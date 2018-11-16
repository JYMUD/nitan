// This program is a part of NT MudLIB

#define TRACE_DETAIL_LENGTH_LIMIT       300
#define SPRINTF_OVERFLOW                65535

// �������ѶϢ�ĺ�ʽ
string tracert_error(mapping error, int caught)
{
        int count;
        string err_msg;
        mapping trace;

        err_msg = "\n"+sprintf(@ERR
����������������������������<Bugs Report>����������������������������
[ ����ʱ�� ]: %-s
[ �������� ]: %-s[m
[ ���󵵰� ]: %-s
[ �������� ]: %-d[m
[ ���ϻ��� ]:
ERR,
        ctime(time()),
        replace_string(error["error"], "\n", " "),
        error["file"],
        error["line"]);

        foreach( trace in error["trace"] )
        {
                count++;
                err_msg +=sprintf(@ERR
    -- �� %|3d �� --
        [ ������� ]: %O
        [ ��ʽ���� ]: %s
        [ ��ʽ���� ]: %s(%s)
        [ �������� ]: %s
ERR,
                count,
                trace["object"],
                trace["program"]||"",
                trace["function"]||"",
                trace["arguments"] ? implode(map(trace["arguments"], (:typeof($1):)), ", ") : "",
                (trace["line"] || "δ֪")+"");

                if( trace["arguments"] )
                {
                        err_msg += "        [ ������� ]:\n";
                        err_msg += implode(map(trace["arguments"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... ѶϢ����ʡ��\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
                if( trace["locals"] )
                {
                        err_msg += "        [ ��ʽ���� ]:\n";
                        err_msg += implode(map(trace["locals"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... ѶϢ����ʡ��\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
        }
        err_msg += "����������������������������<Bugs Report>����������������������������\n\n";
        return err_msg;
}

// simulate the old behavior of the driver
string standard_trace(mapping error, int caught)
{
        int i, s;
        string res;
        object me;
        mixed *cmds;

        /* keep track of number of errors per object...if you're into that */

        res = (caught) ? "����ѶϢ�����أ�" : "";
        res = sprintf("%s\nִ��ʱ�δ���%s\n��ʽ��%s �� %i ��\n�����%s\n",
                      res, error["error"],
                      error["program"], error["line"],
                      error["object"] ? file_name(error["object"]) : "0");

        if( !error["object"] && (me = this_player()) ) {
                res += sprintf("��ǰ��ң�%s(%s) - %O  ���ڻ�����%O\n",
                               me->name(1), query("id", me), me, environment(me));
                cmds = me->query_commands();
                res += me->name(1) + "���ϼ����ܵ���Ʒ�����ڵĻ����ṩ����ָ�\n";
                for(i = 0; i<sizeof(cmds); i++)
                        res += sprintf("%-15s  %2d %O\n",
                                       cmds[i][0], cmds[i][1], cmds[i][2]);

                res += sprintf("��ǰ�����%O\n", me->query_last_input());
        }

        i = 0;
        s = sizeof(error["trace"]);
        if( !this_player(1) && this_player() ) {
                // filter error trace of messaged & chat command
                for (; i < s; i++)
                {
                        string prog;
                        prog = "/" + error["trace"][i]["program"];
                        if( prog != MESSAGE_D + ".c" &&
                            ! sscanf(prog, "/cmds/chat/%*s") &&
                            prog != "/clone/user/chatter.c" &&
                            prog != F_COMMAND )
                                break;
                }
        }

        for (; i < s; i++)
        {
                res = sprintf("%s�������ԣ�%s �� %s() �� %i �У������ %O\n",
                              res,
                              error["trace"][i]["program"],
                              error["trace"][i]["function"],
                              error["trace"][i]["line"],
                              error["trace"][i]["object"]);
        }
        return res;
}

void error_handler(mapping error, int caught)
{
        string msg;
        object user;

        /*
        user = this_player(1);
        if( !objectp(user) ) user = this_player();
        if( !objectp(user) ) user = previous_object();
        */
        user = this_interactive() || this_player() || previous_object();

        efun::write_file(LOG_DIR + "debug.log", standard_trace(error, caught));

        // �����������޴���ر���Ȧ
        if( previous_object() == this_object() )
        {
                if( find_object(CHANNEL_D) )
                        CHANNEL_D->channel_broadcast("debug", "Master object �������޴����Ȧ��"+error["file"]+" �� "+error["line"]+" �У�����"+error["error"]+"����ǿ����ֹ��");
                return;
        }

        msg = tracert_error(error, caught);
        efun::write_file(LOG_DIR + "debug.full", msg);

        if( objectp(user) && userp(user) )
        {
                if( strlen(msg) >= SPRINTF_OVERFLOW-50000 ) msg = msg[0..SPRINTF_OVERFLOW-50000] + "\n\n[ѶϢ����ʡ��...]\n";
                user->set_temp("bug_msg", msg);

                if( !wizardp(user) )
                {
                        tell_object(user, "[1;5;33mWARNING[m ���﷢���˳��棬���� bug ָ���ϸ����������ʦ�������Ա...\n");

                        if( find_object(CHANNEL_D) )
                        {
                                CHANNEL_D->channel_broadcast("debug", user->query_idname()+"ִ��ʱ�δ���"+(caught ? "(Catch)" : "")+"��"+error["file"]+" �� "+error["line"]+" �С�");
                                CHANNEL_D->channel_broadcast("debug", "����"+replace_string(error["error"],"\n", " ")+"��");
                        }
                }
                else
                        tell_object(user, "[1;33mִ��ʱ�δ���[m����ִ�� bug �����ϸ������ݡ�\n"+
                                "[1;33m........����[m��"+error["file"]+"\n[1;33m........����[m���� "+error["line"]+" ��\n[1;33m........����[m��"+replace_string(error["error"],"\n", " ")+"\n");
        }
        else
        {
                if( find_object(CHANNEL_D) )
                {
                        CHANNEL_D->channel_broadcast("debug", (objectp(user) ? base_name(user)+" " : "")+"ִ��ʱ�δ���"+(caught ? "(Catch)" : "")+"��"+error["file"]+" �� "+error["line"]+" �С�");
                        CHANNEL_D->channel_broadcast("debug", "����"+replace_string(error["error"],"\n", " ")+"��");
                }
        }

        return;
}


// Write an error message into a log file. The error occured in the object
// 'file', giving the error message 'message'.
// ��¼��ʾ�������֮ѶϢ
void log_error(string file, string message)
{
        string error_type;
        string name, home;
        object user;


        /*
        user = this_player(1);
        if( !objectp(user) ) user = this_player();
        if( !objectp(user) ) user = previous_object();
        */
        user = this_interactive() || this_player() || previous_object();

        error_type = strsrch(message, "Warning") == -1 ? "����" : "����";

        if( objectp(user) && userp(user) )
        {
                if( !wizardp(user) )
                {
                        if( find_object(CHANNEL_D) )
                                CHANNEL_D->channel_broadcast("debug", user->query_idname()+"����ʱ��"+error_type+"��"+message);
                }
                tell_object(user, "\n����ʱ��"+error_type+"��" + message);
        }
        else
        {
                if( find_object(CHANNEL_D) )
                        CHANNEL_D->channel_broadcast("debug", (objectp(user) ? base_name(user)+" " : "")+"����ʱ��"+error_type+"��"+message);
        }
        efun::write_file(LOG_DIR + "log", message);
}

