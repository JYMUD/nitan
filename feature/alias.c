// alias.c
// Written by Lonely@nitan.org

#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <message.h>
#include <shell.h>

#define MAX_ALIASES             40
#define HISTORY_BUFFER_SIZE     500
#define MAX_DO_COMMANDS         20

#define HISTORY_CMD             0
#define HISTORY_TIME            1

mapping alias;
nosave string *command_history = allocate(0);
nosave int total_command_count;
nosave string last_input, orginal_input;
nosave int last_cmd;
nosave int direct_command;
nosave string *no_busy_cmds = ({
        "hp","score","inventory","look","l","skills","who",
        "id","save","time","uptime","wizlist","version",
        "tell","reply","say",
});

// ������������(�Ѿ�����ALIAS����)
string query_last_input() { return last_input; }

// ��������ԭʼ�ַ���(�Ѿ���������ȷ�ϣ�/��//��ͷ)
string query_orginal_input() { return orginal_input; }

// �Ƿ��ǿ�������(��/��//��ͷ)
int is_direct_command() { return direct_command; }

string process_input(string str);

string remove_leadspace(string arg)
{
        int i;

        if( !stringp(arg) || arg =="" )
                return "";
        for( i = 0; i < strlen(arg); i++ )
                if( arg[i..i] != " " )
                        return arg[i..strlen(arg)];
        return "";
}
nomask string process_history(int i)
{
        int size = sizeof(command_history);
        string cmd;
        
        // ˳���ɺ���ǰ
        if( i < 0 )
        {
                i = -i;
                if( i < 1 ) i = 1;
                else if( i > size ) i = size;
                cmd = (string)command_history[<i][HISTORY_CMD];
        }
        // ˳����ǰ����
        else if( i > 0 )
        {
                if( i > total_command_count || i < 1 || i <= total_command_count - HISTORY_BUFFER_SIZE )
                {
                        tell(this_object(), "ָ�����̷�Χ����\n");
                        return 0;
                }
                if( total_command_count >= HISTORY_BUFFER_SIZE )
                        i -= (total_command_count - HISTORY_BUFFER_SIZE);

                cmd = (string)command_history[i-1][HISTORY_CMD];
        }
        else
        {
                if( size > 0 )
                {
                        cmd = (string)command_history[<1][HISTORY_CMD];
                }
                else
                {
                        tell(this_object(), pnoun(2, this_object()) + "��δ�´��κ�ָ�\n");
                        return 0;
                }
        }
        tell(this_object(), cmd + "\n");
        return cmd;
}

nomask string process_input_basic_parse(string cmd) /* Return 0 if break command input */
{
        switch(cmd[0]) 
        {
                case ''':       //'
                        cmd = "say " + cmd[1..];
                        break;
                case '\"':      //"
                        cmd = "tell " + cmd[1..];
                        break;
                case ']':
                        if( cmd[1] == ']' )
                                cmd = "chat* " + cmd[2..];
                        else
                                cmd = "chat "+ cmd[1..];
                        break;
                case '!':
                        // ָ������
                        {
                                int i;
                                sscanf(cmd, "!%d", i);
                                cmd = process_history(i);
                        }
                default:
                        break;
        }
        return cmd;
}

nomask void process_input_event()
{
        mapping waitback_list;
        object me = this_object();

        if( !mapp(query_temp("waitback_list")) ) return;
        else {
                int time = time();
                int wait_time;
                string msg = "";
                string wait_msg, chinese_time;
                string this_idname = me->query_idname(1);

                waitback_list = query_temp("waitback_list");
                waitback_list = filter(waitback_list, (: objectp($1) :));

                foreach( object usr, mapping info in waitback_list ) {
                        wait_time = info["time"];
                        wait_msg = info["msg"];

                        chinese_time = time_period(time - wait_time);

                        tell_object(usr, HIY "�����" + chinese_time + "��" + this_idname + HIY "���ڻ����ˡ�\n" +
                                         (wait_msg ? "\n���ԣ�" + wait_msg : "") + "\n\a" NOR);
                        msg += HIY + usr->query_idname(1) + HIY "����" + chinese_time + "���������\n" +
                                         (wait_msg ? "\n���ԣ�" + wait_msg : "") + "\n\a" NOR;
                }
                //call_out((: tell(this_object(), $(msg)) :), 0);
                tell_object(me, msg);
                delete_temp("waitback_list");
        }
}

nomask int process_input_do(string verb, string args)
{
        if( verb != "do" ) return 0;
        
        if( args )
        {
                int do_times;
                int total_cmds;

                foreach( string action in explode(args, ",") )
                {
                        do_times = 1;
                        sscanf(action, "%d %s", do_times, action);

                        action = remove_leadspace(action);

                        if( do_times > MAX_DO_COMMANDS ) do_times = MAX_DO_COMMANDS;

                        if( !strsrch(action, "do ") )
                        {
                                tell_object(this_object(), "ָ�� do �в������� do ��ָ�\n");
                                return 1;
                        }

                        while( do_times-- && ++total_cmds )
                        {
                                if( total_cmds > MAX_DO_COMMANDS && !wizardp(this_object()) )
                                {
                                        tell_object(this_object(), "�㲻��һ���³��� "+MAX_DO_COMMANDS+" ��ָ�\n");
                                        return 1;
                                }
                                // ����command������add_action��query_verb������ by Lonely
                                command(process_input(action));
                        }
                }
        }
        else
                tell_object(this_object(), "������Ҫ�����´��ָ�\n");

        return 1;
}

string process_input(string str)
{
        string verb, doargs, *args;
        string cmd, argstr;
        object me, ob;
        int i, j;

        me = this_object();
        notify_fail("ʲô��\n"); 
        clear_written();
        
        if( !living(me) || query_temp("disable_input") ) return "";

        if( !wizardp(me) && query_temp("command_delay") > time() ) return "";

        if( query_temp("dizziness", me) )
        {
                tell_object(me, "��Ŀǰ����ѣ��״̬���޷������κζ�����\n");
                return "";
        }

        // �κ�һ��ָ�������Ĵ���
        process_input_event();

        /*
        if( me->is_busy() && (member_array(str, no_busy_cmds) == -1) ) {
                tell_object(me, BUSY_MESSAGE);
                return "";
        }
        */

        // ��¼��ԭʼ������
        if( str[0] == '/' ) {
                direct_command = 1;
                if (str[1] == '/') str = str[2..<1]; else
                                   str = str[1..<1];
        } else direct_command = 0;

        orginal_input = str;

        // attach system ?
        if( me->is_attach_system() ) {
                me->detach_system();
                tell_object(me, HIR "�û���ֹ�˵�ǰִ�еĽ��̡�\n" NOR);
        }

        if( str == "" ) return str;

        if( me->reject_command() ) {
                tell_object(me, RED "\n\n�ߴ���ʤ��ͻȻ��һ�������г��֡�\n\n\n\n�ߴ���ʤ���ȵ�����ˢ�����죬������ʮ����ϵͳ���ٽ������ָ�\n\n" NOR);
                set_temp("command_delay", time()+10);
                message_vision("$NͻȻһ��ͷ��Ŀѣ��ɵɵ��վ���ⲻ���ˡ�\n", me);
        }

        if( query_temp("big5") )
                //str = B2G(str);
                str = LANGUAGE_D->Big52GB(str);

        //str = remove_fringe_blanks(str);
        str = remove_leadspace(str);
        
        // �����﷨����
        str = process_input_basic_parse(str);

        if( mapp(alias) ) {
                if( !undefinedp(alias[str]) )
                        str = replace_string( alias[str], "$*", "" );
                else if( sscanf(str, "%s %s", cmd, argstr) == 2 && !undefinedp(alias[cmd]) ) {
                        cmd = replace_string( alias[cmd], "$*", argstr );
                        args = explode(argstr, " ");
                        if( (j = sizeof(args)) )
                                for( i=0; i<j; i++ )
                                        cmd = replace_string( cmd, "$" + (i+1), args[i] );
                        str = cmd;
                }
        }
        /*
        if( str[0] == '!' ) {
                if( pointerp(command_history) && sizeof(command_history) ) {
                        if( sscanf(str, "!%d", i) )
                                str = (string)command_history[(HISTORY_BUFFER_SIZE + last_cmd - i) % HISTORY_BUFFER_SIZE];
                        else
                                str = command_history[last_cmd];
                } else
                        return "";
        } else {
                if( !pointerp(command_history) ) command_history = allocate(HISTORY_BUFFER_SIZE);
                last_cmd = (last_cmd + 1) % HISTORY_BUFFER_SIZE;
                command_history[last_cmd] = str;
        }
        */
        // ��¼ָ������
        if( sizeof(command_history) >= HISTORY_BUFFER_SIZE )
                command_history = command_history[1..] + ({ ({ str, time() }) });
        else
                command_history += ({ ({ str, time() }) });

        total_command_count++;
 
         // ����ָ��
        if( sscanf(str, "%s %s", verb, doargs) != 2 ) verb = str;

        if( !doargs || !doargs[0] ) doargs = 0;

        // ��������ָ��
        if( process_input_do(verb, doargs) ) return "";


        if( wizardp(me) && query("env/use_shell") )
                str = parse_shell(str);

        last_input = (string)ALIAS_D->process_global_alias(str);                 
                       
        log_command(last_input);
        return last_input;
}

nomask void clear_history()
{
        command_history = allocate(0);
}

nomask string *query_history()
{
        object this_player = this_player(1);
        
        if( !objectp(this_player) ) return 0;
        
        if( wiz_level(this_player->query_id(1)) < wiz_level(this_object()->query_id(1)) )
                return 0;

        return copy(command_history);
}

nomask int total_command_count()
{
        return total_command_count;
}

int set_alias(string verb, string replace)
{
        if( !replace ) {
                if( mapp(alias) ) map_delete(alias, verb);
                return 1;
        } else {
                if( !mapp(alias) ) alias = ([ verb:replace ]);
                else if( sizeof(alias) > MAX_ALIASES )
                        return notify_fail("���趨�� alias ̫���ˣ�����ɾ��һЩ�����õġ�\n");
                else alias[verb] = replace;
                return 1;
        }
}

mapping query_all_alias()
{
        return alias;
}

int set_ALIAS(mapping data)
{
        if( !mapp(data) ) return 0;
        alias = data;
        return 1;
}
