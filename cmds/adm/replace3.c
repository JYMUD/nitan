// replace.c

#include <ansi.h>
inherit F_CLEAN_UP;

string *deep_file_list(string dir);

int main(object me, string arg)
{
        string str, dir, file, pattern, replace;
        string *result;
        int i;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0; 

        seteuid(geteuid(me)); 

        if (! arg || sscanf(arg, "%s %s to %s", dir, pattern, replace) != 3)
                return notify_fail("ָ���ʽ��replace <Ŀ¼|�ļ���> <ԭ�ַ�> to <���ַ�>\n");

        replace = replace_string(replace, "\\t", "\t"); 
        replace = replace_string(replace, "\\n", "\n"); 
        replace = replace_string(replace, "\"\"", ""); 
                                  
        if (file_size(dir) == -1)
                dir=resolve_path(query("cwd", me),dir);

        if (! SECURITY_D->valid_write(dir, me)) 
                return notify_fail("û���㹻�Ķ�дȨ�ޡ�\n"); 
                
        if (file_size(dir) > 0)
        {               
                str = read_file(dir);
                str = replace_string(str, pattern, replace);                            
                rm(dir);
                if (write_file(dir, str, 1))
                        write(HIW + dir + "�滻�ɹ���\n");
                else 
                        write(HIR + dir + "�滻ʧ�ܡ���\n");
                
                return 1;
        }

        if (file_size(dir) == -2 && file[strlen(dir) - 1] != '/') dir += "/";
        if (file_size(dir) != -2) 
                return notify_fail("û������ļ���Ŀ¼��\n");
                        
        result = deep_file_list(dir);
        
        for (i = 0; i < sizeof(result); i++)
        {
                reset_eval_cost();
                
                file = dir + result[i];
                if (file_size(file) > 0)
                {   
                        str = read_file(file);
                        str = replace_string(str, pattern, replace);                            
                        rm(file);
                        if (write_file(file, str, 1))
                                write(HIW + file + "�滻�ɹ���\n");
                        else 
                                write(HIR + file + "�滻ʧ�ܡ���\n");                                                      
                }                
        }

        return 1;  
}

string *deep_file_list(string dir)
{
        int i;
        string *flist, *result = ({ });
        string file;
        
        flist = get_dir(dir);

        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];
                
                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/");
                else 
                        result += ({ file });

        }
        return result;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: replace <Ŀ¼|�ļ���> <ԭ�ַ�> to <���ַ�>
���ļ������������<ԭ�ִ�>ת����<���ִ�>��
ע������ָ��Ŀ¼���ǻ������Ŀ¼�µ�����Ŀ¼��ȡ�ļ���������ҪС��ʹ�ã�
HELP );
        return 1;
}



