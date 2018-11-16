// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <command.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *data;
        string type, id;
        object  target;
        int     i, t, total, size;

        seteuid(ROOT_UID);

        MYGIFT_D->check_mygift(me, "newbie_mygift/msg");   

        if( arg == "clear" ) {
                me->clear_msg_log();
                write("��������е�ѶϢ��¼��\n");
                me->save();
                return 1;
        }

        if( arg == "system" ) {
                t=query("msg/time", me);
                if( !t ) {
                        tell_object(me, WHT "��ӭ������" + LOCAL_MUD_NAME() +
                                        WHT "�������ʹ��" HIY " msg " NOR WHT
                                        "��������ʼ���Ϣ��\n" NOR);
                        set("msg/time", time(), me);
                        return 1;
                }
                data = me->query_mail();
                if( !arrayp(data) || !sizeof(data) ) {
                        tell_object(me, HIY "��û���յ����ʼ���\n" NOR);
                        return 1;
                }

                size = sizeof(data);
                total = 0;
                for( i=size-1;i>=0;i-=3 ){
                        if( to_int(data[i-2]) > t )
                                total++;
                        else
                                break;
                }
                if( !total )
                        tell_object(me, HIY "��Ŀǰû��δ���Ķ������ʼ���\n" NOR);
                else
                        tell_object(me, sprintf(WHT "��Ŀǰһ���� " HIY "%d" NOR
                                        WHT " ���ʼ���û���Ķ�����ʹ��("
                                        HIY "msg" NOR WHT ")�����Ķ���\n" NOR, total));
                return 1;
        }
        if( arg == "info" ) {
                mapping setup=query("msg", me);

                if( !mapp(setup) || !sizeof(keys(setup)-({ "size" })) )
                        return notify_fail("û���趨��¼�κ�ѶϢ��\n");

                map_delete(setup, "size");
                write("Ŀǰ�趨��ѶϢ��¼��Ŀ��"+implode(keys(setup), ", ")+"\n");
                return 1;
        }

        if( arg && (size = to_int(arg)) ) {
                if( size < 10 || size > 1000 )
                        return notify_fail("ѶϢ���ټ�¼ 10 �ʣ�����¼ 1000 �ʡ�\n");

                set("msg/size", size, me);
                write("�趨ѶϢ��¼����Ϊ "+size+" �ʡ�\n");
                me->save();
                return 1;
        }

        if( arg && sscanf(arg, "mail %s", id) == 1 ) {
                if( !wizardp(me) && time()-query_temp("last_mail_msg", me)<60 )
                        return notify_fail(HIC "����һ������ֻ�ܷ���һ������Ϣ��\n" NOR);

                if( id == query("id", me) )
                        return notify_fail(HIC "����û�����⣬�Լ����Լ�д��Ϣ����\n" NOR);

                target = UPDATE_D->global_find_player(id);

                if( !objectp(target) )
                        return notify_fail("û�������ҡ�\n");

                UPDATE_D->global_destruct_player(target, 1);

                /*
                if( !wizardp(me)
                     && !MEMBER_D->is_valid_member(query("id", me) )
                    && id != "lonely" )
                          return notify_fail("ֻ�л�Ա���ܷ��Ͷ���Ϣ��\n");
                */

                set_temp("last_send_msg", time(), me);
                write(HIG "���������Ϣ���ݣ����Ȳ�����500�����֣���\n" NOR);

                me->edit(bind((: call_other, __FILE__, "done", me, id :), me));

                return 1;
        }
        else if( arg && sscanf(arg, "+%s", type) == 1 ) {
                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) ) {
                        set("msg/"+type, 1, me);
                        write("��ʼ��¼ "+type+" ��ѶϢ��\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("�޷��趨 "+type+" ����ѶϢ��\n");
        }
        else if( arg && sscanf(arg, "-%s", type) == 1 ) {

                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) ) 
                {
                        delete("msg/"+type, me);
                        write("ֹͣ��¼ "+type+" ��ѶϢ��\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("�޷��趨 "+type+" ����ѶϢ��\n");
        }

        if( wizardp(me) && arg && objectp(target = find_player(arg)) && wiz_level(target) <= wiz_level(me) )
                data = target->query_msg_log();
        else
                data = me->query_msg_log();

        size = sizeof(data);

        if( size ) {
                string *str;

                str = ({ (target?target->query_idname():"")+"���� "+(size/3)+" �ʾ�ѶϢ��¼��\n��������������������������������������������������������������������������\n" });

                if( arg && !target ) {
                        for(i=0;i<size;i+=3)
                                if( data[i+1] == arg )
                                        str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                        //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                }
                else {
                        for(i=0;i<size;i+=3)
                                   str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                }

                str += ({ "��������������������������������������������������������Ŀǰʱ�� "HIW+ctime(time())[11..15]+NOR"����\n" });
                me->start_more(implode(str, ""));
                set("msg/time", time(), me);
                me->save();
        }
        else
                write(target?target->query_idname():""+"Ŀǰû���κ�ѶϢ��¼��\n");

        return 1;
}

void done(object me, string id, string msg)
{
        object ob;
        string mail, *mail_log;

        if( !me || !msg || msg == "" )
                return;

        // ��鳤��
        if( sizeof(msg) > 1000 ) {
                write("����Ϣ����������ܴ���1000���ֽڡ�\n");
                return;
        }

        msg = replace_string(msg, "\"", "");
        if( objectp(ob = find_player(id)) ) {
                if( !wizardp(me) && ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "�Ķ���Ϣ������\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "���ʼ���Ϣ������" + me->query_idname() + HIR "���ʼ���������\n"HIW+msg+NOR"\n");
                ob->save();
                tell_object(ob, HIR "���ʼ���Ϣ�������յ�һ������" + me->query_idname() + HIR "���ʼ�(msg mail)��\n" NOR);
        } else {
#ifdef DB_SAVE
                mail = DATABASE_D->db_query_player(id, "f_mail");
                mail_log = restore_variable(mail);
                if( !arrayp(mail_log) ) mail_log = ({});

                if( wiz_level(id) < 1 ) {
                        if( !wizardp(me) && sizeof(mail_log) >= 60 ) {
                                tell_object(me, "�Է��Ķ���Ϣ������\n");
                                return;
                        }
                } else {
                        if( sizeof(mail_log) >= 300 ) {
                                tell_object(me, "�Է��Ķ���Ϣ������\n");
                                return;
                        }
                }
                msg = HIR "���ʼ���Ϣ������" + me->query_idname() + HIR "���ʼ���������\n"HIW+msg+NOR"\n";
                mail_log += ({ time(), "mail", msg });

                mail = save_variable(mail_log);
                DATABASE_D->db_set_player(id, "f_mail", mail);
#else
                ob = UPDATE_D->global_find_player(id);
                if( ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "�Ķ���Ϣ������\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "���ʼ���Ϣ������" + me->query_idname() + HIR "���ʼ���������\n"HIW+msg+NOR"\n");
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1);
#endif
        }

        tell_object(me, HIY "���ʼ���Ϣ����Ķ���Ϣ�Ѿ��ɹ����ͣ�\n" NOR);
        return;
}

int help(object me)
{
        write(@HELP
��ʾ����յ��� 1000 ������/ҥ��Ƶ����������ѶϢ��

msg                     �鿴����ѶϢ�ļ�¼
msg ����                �鿴ĳ��ѶϢ�ļ�¼������ msg mail ����鿴 mail ��Ϣ
msg +����               ����ĳ��ѶϢ�ļ�¼
msg -����               ֹͣĳ��ѶϢ�ļ�¼
msg ����                �趨ѶϢ��¼���������ټ�¼ 10 �ʣ�����¼ 1000 ��
msg clear               ɾ������ѶϢ
msg info                ��ѯĿǰ��ѶϢ��¼��Ŀ
msg mail <ĳ��>         ��ĳ��(��������)����

ѶϢ�������������Ƶ��(chat, rumor, ...), say, tell, ...

HELP );
        return 1;
}
