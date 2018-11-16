#include <ansi.h>
#include <feature.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
ָ���ʽ��fgrep [-l] [-r] <��ʽ> [·��]

��ʾ�������������ʽ�ĵ���, <��ʽ> ��Ϊ�����ʾ��(regular expression)
��֪�����ʾ�����÷��� help regexp() ��ȡ�ø���һ����Ѷ��

��ز���˵�����£�

-l      ��ʾ�к�
-r      ��ʾ������ <��ʽ> ��
HELP;
string last_file;
mapping grep(string path, string *files, string pattern, int flag);
private void command(object me, string arg)
{
        string path, *files;
        mapping match_files;
        int fsize, flag, gcnt, fcnt;

        if( !arg )
        {
                printf("ָ���ʽ��fgrep [-l] [-r] <��ʽ> [·��]\n");
                return;
        }
        if( sscanf(arg, "-l %s", arg) ) flag  = 1;
        if( sscanf(arg, "-r %s", arg) ) flag += 2;
        if( sscanf(arg, "'%*s' %*s") == 2 )
                sscanf(arg, "'%s' %s", arg, path);
        else if( sscanf(arg, "'%*s'") )
                sscanf(arg, "'%s'", arg);
        else if( sscanf(arg, "%*s %*s") == 2 )
                sscanf(arg, "%s %s", arg, path);

        if( arg )
        {
                int idx, chr, marked, i, j;
                for(idx=0; idx<strlen(arg); idx++)
                {
                        chr = arg[idx];
                        marked = idx && arg[idx-1] == '\\';
                        if( chr == '(' && !marked ) i++;
                        if( chr == ')' && !marked ) i--;
                        if( chr == '[' && !marked ) j++;
                        if( chr == '[' && !marked ) j--;
                }
                if( i )
                {
                        printf("fgrep: ���� <��ʽ> ��ʽ����() ����Ϊһ�ԡ�\n", arg);
                        return;
                }
                if( j )
                {
                        printf("fgrep: ���� <��ʽ> ��ʽ����[] ����Ϊһ�ԡ�\n", arg);
                        return;
                }
        }
        
        path = resolve_path(me, path);
        
        fsize = file_size(path);
        
        if( fsize == -2 )
        {
                if( path[<1] != '/' ) path += "/";
                files = get_dir(path);
        }
        else
        {
                int idx = strsrch(path, '/', -1);
                files = get_dir(path);
                path = path[0..idx];
        }
        if( !files )
                return tell(me, "fgrep: û�� " + path + " ���������Ŀ¼��\n", CMDMSG);

        if( !sizeof(files) )
                return tell(me, "fgrep: �� " + path + " Ŀ¼��û���κε�����\n", CMDMSG);

        tell(me, sprintf(HIY"��Ѱ��ʽ"HIW" %s "NOR + HIY"�� %s ... \n\n"NOR, arg, path), CMDMSG);
        
        match_files = grep(path, files, arg, flag);
        foreach(string file, mixed match in match_files)
        {
                gcnt = sizeof(match);
                if( !gcnt ) continue;
                for(int i=0; i<gcnt; i++)

                {
                        if( flag%2 && !(i%2) )
                        {
                                tell(me, sprintf(HIW"%4d- "NOR, match[i+1]), CMDMSG);
                        }
                        
                        tell(me, sprintf("%s\n"NOR, match[i]), CMDMSG);
                        if( flag ) i++;
                }
                if( flag ) gcnt = gcnt/2;
                tell(me, sprintf(HIR"�� %s �����й��ҵ� %d �����Ͻ����\n\n"NOR, path + file, gcnt), CMDMSG);
                fcnt ++;
        }
        
        tell(me, sprintf(HIY"�� %d ���������ϱȶ���ʽ��\n"NOR, fcnt), CMDMSG);
}

mapping grep(string path, string *files, string pattern, int flag)
{
        string *lines;
        mapping match_files = allocate_mapping(0);
        mixed match;

        if( path[<1] != '/' ) path += "/";
        foreach(string file in files)
        {
                last_file = path + file;
                if( file_size(last_file) < 0 ) continue;
                lines = explode(read_file(path + file), "\n");
                match = regexp(lines, pattern, flag);
                if( match ) match_files[file] = match;
        }
        return match_files;
}
string query_last_file()
{
        return last_file;
}

