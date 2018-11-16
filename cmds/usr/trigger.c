// trigger.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define MAX_TRIGGER_CMDS  10
#define TRIGGER_CMD_SIZE  21

protected void done_input(object me, string text);
protected void user_quit(object me);
int  continue_trigger(object me);
int  cancel_trigger(object me);

int main(object me, string arg)
{
        object ob;
        object env;
        string msg, filename, file, *lines;
        string tg_msg, tg_cmd;
        int i, n, line;

        seteuid(getuid());

        filename=DATA_DIR+"trigger/"+query("id", me)+__SAVE_EXTENSION__;
        if( !arg) {
                if( file_size(filename) > 0 ) {
                        write(HIC"��Ŀǰ���趨�еĴ������£�\n"NOR);
                        file = read_file(filename);
                        msg = HIW"";

                        lines = explode(file, "\n");
                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                        tg_cmd = replace_string(tg_cmd, ",", ";");
                                        msg += "-----------------------------------------------\n";
                                        msg += "(" + chinese_number(i+1) + ")\n";
                                        msg += HIY"�����ַ���"HIW + tg_msg + "\n";
                                        msg += HIY"����ָ�"HIW + tg_cmd + "\n";
                                        msg += "-----------------------------------------------\n";
                                }
                        }

                        msg += "\n"NOR;
                        me->start_more(msg);

                        return 1;
                }
                else
                        return notify_fail(HIW"ָ���ʽ��trigger �����ַ�:ִ��ָ��\n"HIY"[��ʾ���������ö��ָ�ÿ��ָ��֮���ö���[,]�����]\n"NOR);
        }

        if( arg == "clear" ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("����������ִ�д���������ͣ�������������\n");

                delete("trigger", me);
                if( file_size(filename) >= 0 ) {
                        rm(filename);
                        write(HIW"�ɹ�����������á�\n"NOR);
                        return 1;
                } else {
                        write(HIW"�㲢û�����ô�����\n"NOR);
                        return 1;
                }
        }

        if( sscanf(arg, "rm %d", line) ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("����������ִ�д���������ͣ�������������\n");

                if( file_size(filename) > 0 ) {
                        file = read_file(filename);
                        lines = explode(file, "\n");

                        if( line > sizeof(lines) )
                                return notify_fail(HIY"�� " + chinese_number(line) +" ���������ò����ڡ�\n"NOR);

                        msg = "";

                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( i + 1 == line ) {
                                        if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                                tg_cmd = replace_string(tg_cmd, ",", ";");
                                                write(HIR"��ɹ�ɾ����" + chinese_number(line) + "���������£�\n");
                                                write("-----------------------------------------------\n");
                                                write(HIY"�����ַ���"HIW + tg_msg + "\n");
                                                write(HIY"����ָ�"HIW + tg_cmd + "\n");
                                                write("-----------------------------------------------\n");
                                        }

                                        continue;
                                }

                                msg += lines[i] + "\n";
                        }
                        rm(filename);
                        write_file(filename, msg, 1);
                        return 1;
                }
                else
                        return notify_fail(HIY"��Ŀǰ��û�д������á�\n"NOR);
        }
        if( arg == "start" ) {
                if( file_size(filename) < 1 )
                        return notify_fail("��Ŀǰ��û���ƶ�������\n");

                if( query("trigger", me) )
                        return notify_fail(HIY"�㲢û�йرմ������ܣ�����Ҫ�ٿ�����\n"NOR);

                if( query("doing", me) )
                        return notify_fail("����������æ�ڶ��������ܿ�չ�´�����\n");

                env = environment(me);
                if( !env )
                        return notify_fail("������ʲô�������ˡ�\n");

                if( env->is_chat_room() )
                        return notify_fail("�㲻��������������ִ�мƻ���\n");

                if( query("combat_exp", me)<5000 )
                        return notify_fail("���ʵս����̫ǳ���������Ⱥúö���������˵�ɡ�\n");

                if( query("potential", me)-query("learned_points", me)<100 )
                        return notify_fail("���Ǳ��̫�٣����Կ�չ������\n");

                if( sizeof(filter_array(all_inventory(env), (: userp :))) > 12 )
                        return notify_fail("�������ʵ��̫���ˣ������Ծ��Ŀ�չ������\n");

                addn("learned_points", 100, me);

                file = read_file(filename);
                set("trigger", file, me);
                write(HIG"�㿪���˴������ܡ�\n"NOR);
                set("startroom", base_name(env), me);
                CLOSE_D->user_closed(me);
                me->set_short_desc(0);
                continue_trigger(me);
                return 1;
        }

        if( query("doing", me) == "trigger" )
                return notify_fail("����������ִ�д���������ͣ�������޸ġ�\n");

        if( strlen(arg) > 300 )
                return notify_fail(HIY"��Ĵ����趨̫���ˣ��������300���ֽ����ڣ�\n"NOR);

        if( file_size(filename) > 0 ) {
                file = read_file(filename);
                lines = explode(file, "\n");

                if( sizeof(lines) >= TRIGGER_CMD_SIZE )
                        return notify_fail(HIY"��ֻ������" + chinese_number(TRIGGER_CMD_SIZE) + "����������Ҫɾ��һЩ�������ܼ������á�\n"NOR);
        }

        if( sscanf(arg, "%s:%s", tg_msg, tg_cmd) ) {
                if( !tg_msg || !tg_cmd )
                        write(HIW"���Ӵ���ʧ�ܡ�\n"NOR);
                else
                if( write_file(filename, tg_msg + ":" + tg_cmd + "\n") ) {
                        tg_cmd = replace_string(tg_cmd, ",", ";");
                        write(HIG"��ɹ�������һ���������£�\n");
                        write("-----------------------------------------------\n");
                        write(HIY"�����ַ���"HIW + tg_msg + "\n");
                        write(HIY"����ָ�"HIW + tg_cmd + "\n");
                        write("-----------------------------------------------\n");
                }
                else
                        write(HIW"���Ӵ���ʧ�ܡ�\n"NOR);
        }
        else
                return notify_fail(HIW"ָ���ʽ��trigger �����ַ�:ִ��ָ��\n"HIY"[��ʾ���������ö��ָ�ÿ��ָ��֮���ö���[,]�����]\n"NOR);

        return 1;

}

// ��ʼִ�д���
int continue_trigger(object me)
{
        if( !query("trigger", me) )
                return 0;

        set("doing", "trigger", me);
        me->set_override("unconcious", (: call_other, __FILE__, "cancel_trigger" :));
        me->set_override("die", (: call_other, __FILE__, "cancel_trigger" :));
        return 1;
}

// ��ֹ����
int cancel_trigger(object me)
{
        me->delete_override("unconcious");
        me->delete_override("die");

        if( !query("trigger", me) )
                return 0;

        delete("trigger", me);
        delete_temp("trigger", me);
        CLOSE_D->user_opened(me);

        if( !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 0);

        return 0;
}

// ִ�д�����
void execute_trigger(object me)
{
        string cmd, *cmds, *run;
        string cmd_buffer;
        int i, n;

        if( !objectp(me) || previous_object() != me )
                return;

        if( !(cmd=query_temp("trigger", me)) )
                return;

#ifndef NO_FEE
        if( !interactive(me) &&
            !me->is_vip() && query("online_time", me) <= query("offline_time", me)*3){
                cancel_trigger(me);
                return;
        }
#endif

        cmds = explode(cmd, ",");
        n = sizeof(cmds);
        run = ({ });

        for( i=0; i<n; i++ ) {
                if( i >= MAX_TRIGGER_CMDS ) break;
                if( me->is_busy() || !living(me) ) break;
                if( query("jing", me)*100/query("max_jing", me)<5 || 
                    query("qi", me)*100/query("max_qi", me)<5 )
                        break;
                if( query_temp("block_msg", me) || me->is_block_cmds() )
                        break;

                me->force_me(cmds[i]);
                run += ({ cmds[i] });
        }

        cmds -= run;

        if( !arrayp(cmds) || !sizeof(cmds) ) {
                delete_temp("trigger", me);
        } else {
                cmd_buffer = implode(cmds, ",");
                set_temp("trigger", cmd_buffer, me);
        }

        return;
}

void user_quit(object me)
{
        if( !is_root(previous_object()) &&
            previous_object() != me )
                return;

        if( !objectp(me) )
                return;

        me->force_me("quit");

        if( objectp(me) && !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 5);
}

int help (object me)
{
       write(@HELP
ָ���ʽ��
[һ]������һ��������trigger �����ַ�:ִ��ָ��
      ���磺���봥�����˹���ϡ���Ҳ������Ļ�ϳ��֡��˹���ϡ����Ҿ�
      �����������ڣ���ô���ǿ�����������ô���ã�
      trigger �˹����:dazuo 100
      ִ�п�������ᷢ��ֻҪ��Ļ��һ���֡��˹���ϡ���Щ�֣�ϵͳ�ͻ�
      �Զ�������100������������
      Ҳ������ʣ����������Ļ�ϳ��֡��˹���ϡ����ȶ���һ���ٴ�����
      Ҳ������Ļ�ϳ��֡��˹���ϡ�ʱͬʱִ������ָ�����ô�����أ�
      �ܼ򵥣���ֻ��Ҫ�Ѹ���ָ��֮���ö���[,]������Ϳ����ˡ����£�
      trigger �˹����:study book,dazuo 100
      ϵͳ�ͻ�����Ļ�ϳ��֡��˹���ϡ�ʱ���Ȱ���������һ���ٴ����ˡ�
      ��ȻҲͬ���߼ƻ�����һ��Ҳ��֧�� alias ��ָ��ġ�
[��]���鿴���õ����д�����trigger
[��]��ɾ��һ��������trigger rm ����
      ˵����������־�����Ҫɾ��������������λ�ã�����ͨ���鿴��Ҫɾ
      ��������������λ�á�
[��]��ɾ�����д�����trigger clear
[��]���رմ�����halt
[��]������������trigger start

see also: scheme
HELP
        );
        return 1;
}
