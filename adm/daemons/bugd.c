// This program is a part of NT MudLIB

#include <ansi.h>
#include <mudlib.h>

#define DATA_PATH               "/data/bug/"
#define DEFAULT_LOAD            10
#define SERIAL_NUMBER_KEY       "bug"

#define REPLY_AUTHOR            0
#define REPLY_MESSAGE           1

#define LIST_OPT_ALL    (1<<0)

string *buginfo;

int bug_exists(string number)
{
        return file_exists(DATA_PATH+number);
}

void reset_buginfo()
{
        buginfo = allocate(0);

        foreach(string file in sort_array(get_dir(DATA_PATH), (: (to_int($1) < to_int($2)) ? 1 : -1 :))[0..DEFAULT_LOAD-1])
                buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
}

// �г� Bug �б�
string list_bug(int options)
{
        int len;
        string listmsg;
        string *list_buginfo;

        if( options & LIST_OPT_ALL )
        {
                list_buginfo = allocate(0);

                foreach(string file in get_dir(DATA_PATH))
                        list_buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
        }
        else
                list_buginfo = buginfo;

        list_buginfo = sort_array(list_buginfo, (: (to_int($1["number"]) < to_int($2["number"])) ? 1 : -1 :));
        listmsg =  "\n"+MUD_FULL_NAME+HIY" ����ر�ϵͳ\n"NOR;
        listmsg += WHT"��������������������������������������������������������������������������\n"NOR;
        listmsg += "��� �ر���                   ����                          ����״̬  ��Ӧ\n";
        listmsg += WHT"��������������������������������������������������������������������������\n"NOR;

        foreach( mapping data in list_buginfo )
        {
#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif
                listmsg += sprintf(HIY"%-4s"NOR" %-24s %-:30s%-"+(8+len)+"s %5s\n", data["number"],
                                   data["author_idname"], data["title"], data["status"],
                                   sizeof(data["reply"]) ? sizeof(data["reply"])+"" : "");
        }
        listmsg += WHT"��������������������������������������������������������������������������\n"NOR;

        if( options & LIST_OPT_ALL )
                listmsg += "�г����лر�����\n";
        else
                listmsg += "�г���� "+DEFAULT_LOAD+" ��ر�����\n";

        return listmsg;
}

// ���� Bug ����
string add_bug(object me, string title, string content)
{
        mapping bugdata = allocate_mapping(0);

        if( !objectp(me) || !stringp(title) || !stringp(content) )
                error("BUG_D add_bug() �����������");

        bugdata["time"] = time();
        bugdata["where"] = base_name(environment(me));
        bugdata["number"] = SERIAL_NUMBER_D->query_serial_number(SERIAL_NUMBER_KEY);

        bugdata["author_id"] = me->query_id(1);
        bugdata["author_idname"] = me->query_idname();

        bugdata["title"] = title;
        bugdata["content"] = content;

        bugdata["status"] = HIR"δ����"NOR;

        bugdata["reply"] = allocate(0);

        assure_file(DATA_PATH+bugdata["number"]);
        if( write_file(DATA_PATH+bugdata["number"], save_variable(bugdata)) )
                reset_buginfo();
        else
                error("BUG_D �޷��������� bug ����");

        CHANNEL_D->channel_broadcast("sys", HIW+me->query_idname()+HIW"���� Bug �ر�����"+title+NOR+HIW"������ţ�"+bugdata["number"]+"��");

        return bugdata["number"];
}

// ��Ӧ Bug ��������
varargs void reply_bug(object me, string number, string status, string message)
{
        mapping data;

        if( !bug_exists(number) )
                error("BUG_D reply_bug() �޴˵���");
        else
                data = restore_variable(read_file(DATA_PATH+number));

        data["status"] = status;
        CHANNEL_D->channel_broadcast("sys", me->query_idname()+"�޸ı�ŵ� "+number+" �� Bug ����״��Ϊ��"+status+"��");

        if( find_player(data["author_id"]) )
                tell_object(find_player(data["author_id"]), me->query_idname()+"��Ӧ��ŵ� "+number+" �� Bug ����״��Ϊ��"+status+"����\n");

        if( !undefinedp(message) )
        {
                if( !arrayp(data["reply"]) )
                        data["reply"] = allocate(0);

                data["reply"] += ({ ({ me->query_idname(), message }) });
                CHANNEL_D->channel_broadcast("sys", me->query_idname()+"�����ŵ� "+number+" �� Bug �����Ӧ");
        }

        write_file(DATA_PATH+number, save_variable(data), 1);
        reset_buginfo();
}

// �Ƴ� Bug ����
varargs void remove_bug(object me, string number, int reply)
{
        if( !bug_exists(number) )
                error("BUG_D remove_bug() �޴˵���");

        // ɾ������ Bug ��Ѷ
        if( undefinedp(reply) )
        {
                if( !rm(DATA_PATH+number) )
                        error("BUG_D remove_bug() �޷�ɾ������");

                reset_buginfo();
        }
        // ɾ������һ����Ӧ����
        else
        {
                mapping data = restore_variable(read_file(DATA_PATH+number));

                reply--;

                if( reply < sizeof(data["reply"]) && reply >= 0 )
                {
                        if( reply == 0 )
                                data["reply"] = data["reply"][1..];
                        else
                                data["reply"] = data["reply"][0..reply-1] + data["reply"][reply+1..];
                }

                write_file(DATA_PATH+number, save_variable(data), 1);
                reset_buginfo();
        }
}

// ��ѯ Bug ����
string query_bug(string number)
{
        string bugmsg;
        mapping data;
        int len;

        if( !bug_exists(number) )
                error("BUG_D query_bug() �޴˵���");
        else
                data = restore_variable(read_file(DATA_PATH+number));

#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif

        bugmsg =  sprintf(HIM"���"NOR" %-20s "HIM"����"NOR" %s\n"NOR, data["number"], data["title"]);
        bugmsg += sprintf(HIM"ʱ��"NOR" %-20s "HIM"�ر�"NOR" %s\n", TIME_D->replace_ctime(data["time"]), data["author_idname"]);
        bugmsg += sprintf(HIM"״��"NOR" %-"+(20+len)+"s "HIM"��Ӧ"NOR" %d\n", data["status"], sizeof(data["reply"]));
        bugmsg += sprintf(HIM"�ص�"NOR" %s\n", data["where"]);
        bugmsg += WHT"��������������������������������������������������������������������������\n"NOR;
        bugmsg += data["content"]+"\n";

        if( sizeof(data["reply"]) )
        {
                int replies;

                foreach( string *reply in data["reply"] )
                {
                        replies++;
                        bugmsg += HIY"\n\n*** �� "+replies+" ƪ��Ӧ��"+reply[REPLY_AUTHOR]+HIY+" ***\n"NOR;
                        bugmsg += reply[REPLY_MESSAGE]+NOR"\n";
                }
        }

        bugmsg += WHT"��������������������������������������������������������������������������\n"NOR;

        return bugmsg;
}

void create()
{
        reset_buginfo();
}
string query_name()
{
        return "����ر�ϵͳ(BUG_D)";
}
