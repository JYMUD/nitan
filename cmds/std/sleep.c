// sleep.c
// Updated by Lonely

#include <ansi.h>
#include <command.h>

void wakeup(object me);

int main(object me, string arg)
{
        object obj, old_target;
        int i;
        object *inv;
        mapping fam;
        mapping cnd;
        string *kc;
        object where = environment(me);
        object bag;
        int qi, jing;

        seteuid(getuid());

        if (! where) return 1;

        if( (!(fam=query("family", me)) || fam["family_name"] != "ؤ��" )
              && !(query("sleep_room", where) )
             && !objectp(bag = present("sleepbag", me))
              || (query("no_sleep_room", where)) )
             return notify_fail("���ﲻ������˯�ĵط���\n");


        if (me->is_busy())
                return notify_fail("����æ���أ�\n");

        if( me->is_fighting() )
                return notify_fail("ս���в���˯����\n");

        if( query("hotel", where) && !(query_temp("rent_paid", me)) )
        {
                message_vision("��С���������$N��У�������"
                               "�������������ȵ�һ¥��Ǯ������˯��\n",me);
                return 1;
        }

        jing=query("jing", me);
        qi=query("qi", me);
        if (jing < 0 || qi < 0)
                return notify_fail("�����ڽӽ����ԣ�˯���ž���\n");
        cnd = me->query_condition();
        if (cnd && sizeof(cnd))
        {
                kc   = keys(cnd);
                for (i = 0; i < sizeof(kc); i++)
                {
                        if (CONDITION_D(kc[i])->min_qi_needed(me) > qi ||
                            CONDITION_D(kc[i])->min_jing_needed(me) > jing)
                        {
                                message("vision", me->name() + "����������˯����"
                                        "����շת���࣬����˯���š�\n",
                                        environment(me), me);
                                tell_object(me, "��������۾��ú�˯��һ��������" +
                                            to_chinese(kc[i]) + "������ĥ���㣬"
                                            "����շת���ߡ�\n");
                                return 1;
                        }
                }
        }

        if( query("sleep_room", where) )
        {
            write("��������һ�ɣ���ʼ˯����\n");
            write("��һ�������ͽ��������硣\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$Nһ�������ڴ��ϣ���һ��"
                           "���������������������硣\n",me);
        } else
        if (objectp(bag = present("sleepbag", me)))
        {
                write("��չ��һ��˯�������˽�ȥ����ʼ˯��\n");
            write("��һ�������ͽ��������硣\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$Nչ��һ��˯�������˽�ȥ����һ��ͽ��������磡\n",me); 
        } else
        {
            write("�������½���һ�ɣ���ʼ˯����\n");
            write("��һ�������ͽ��������硣\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N�����½�������һ�ɣ���һ"
                           "�����������������������\n",me);
        }

        set("no_get", 1, me);
        set("no_get_from", 1, me);

        set_temp("sleeped", 1, me);
        if( query("hotel", where) )
            delete_temp("rent_paid", me);

        me->disable_player(" <˯����>");
        me->start_call_out(bind((: call_other, __FILE__, "wakeup", me :), me),
                           3 + random(120/me->query_con()));

        return 1;
}

void wakeup(object me)
{
        if( !me || !query_temp("sleeped", me) )
                return;

        if (living(me))
        {
                delete_temp("sleeped", me);
                return;
        }

        me->enable_player();
        set_temp("block_msg/all", 0, me);
        delete("no_get", me);
        delete("no_get_from", me);
        delete_temp("sleeped", me);

        // if (time() - me->query("last_sleep") >= 30)
        if (time())
        {
                set("qi",query("eff_qi",  me), me);
                set("jing",query("eff_jing",  me), me);
                if( query("neili", me)<query("max_neili", me) )
                        set("neili", query("max_neili", me), me);
                /*
                me->add("neili",query("max_neili", me)/2-
                                 query("neili", me)/2);
                */
                message("vision", me->name() + "һ����������������"
                                  "�ػ��һ�½�ǡ�\n",
                        environment(me), ({ me }));
                write("��һ��������ֻ���������档�ûһ���ˡ�\n");
                set("last_sleep", time(), me);
        } else
        {
                message("vision", me->name() + "���Ժ����������۾���"
                                  "��ɢ���������������\n",
                        environment(me), ({ me })); 
                write("�����Ժ���������˫�ۣ�����������\n");
        }
        me->write_prompt();
}

int help(object me)
{
        write(@HELP
ָ���ʽ : sleep
 
����˼�壬���ָ��������˯���ġ�
HELP );
        return 1;
}
