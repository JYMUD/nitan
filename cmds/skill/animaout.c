// animaout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int outing(object me);
int halt_outing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( !query("breakup", me) )
                return notify_fail("�㻹û�д�ͨ��С���죬̸ʲôԪӤ������\n");

        if( query("animaout", me) )
                return notify_fail("���Ѿ�����ԪӤ�����ˣ�û�б�Ҫ����һ�飡\n");

        if( query("reborn/times", me) < 1 )
                return notify_fail("�㻹û��ת��������������������ԪӤ������\n");

        if (wizardp(me))
                return notify_fail("��ʦҲҪ����ԪӤ��������ë���ˣ�\n");

        if( !query("no_fight", where) )
                return notify_fail("����������ԪӤ��������̫��ȫ�ɣ�\n");

        if( !query("sleep_room", where) )
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չ����С�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( query("potential", me)-query("learned_points", me)<1000 )
                return notify_fail("���Ǳ�ܲ�����û���չ�����������ԪӤ������\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

        if( query("max_jingli", me)<2000 )
                return notify_fail("����þ������в��㣬����Ŀǰ������"
                                   "����ԪӤ������\n");

        if( query("jingli", me)*100/query("max_jingli", me)<90 )
                return notify_fail("�����ڵľ���̫���ˣ��޷����ıչء�\n");

        message_vision("$N��ϥ���£���ʼڤ���˹����չ����С�\n", me);
        set("startroom", base_name(where), me);
        set("doing", "animaout", me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)��ʼ�չ����У���������ԪӤ������",
                              ultrap(me) ? "����ʦ" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_outing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n������չ�����������ԪӤ����...\n" NOR);
        return 1;
}

protected void stop_outing(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int outing(object me)
{
        string msg;

#ifndef NO_FEE
        if (! interactive(me) &&
            ! me->is_vip()) &&
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "��û�а취����������ȥ�ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�չؽ������ƺ�û��ʲô�ɹ���",
                                      me->name(1),query("id", me)));
                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        addn("learned_points", 1, me);

        if (random(10))
                return 1;

        if( random(40000)<query("con", me) )
        {
                message_vision(HIY "ֻ��$N" HIY "ͷ���ֳ�����������"
                               "�����䣬һʱ�������˱ǡ��뵱�أ�\n" NOR, me);
                tell_object(me, HIM "����þ���ԴԴ��������Ȼ����ֹˮ�������"
                            "��ʣ���Դ�޾�����ʱ�󳹴���\n" NOR);
                set("animaout", 1, me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�����չؿ��ޣ���"
                                      "���޳�����������ԪӤ������",
                                      me->name(1),query("id", me)));
                addn("max_jingli", 1500, me);
                CHAR_D->setup_char(me);
                stop_outing(me);
                return 0;
        }

        switch (random(4))
        {
        case 0:
                msg = "���������飬��ס�������Լ��ľ�����\n";
                break;

        case 1:
                msg = "�㽫��������Ԫ����ͼ�������硣\n";
                break;

        case 2:
                msg = "����ͼ��Ԫ��Ƴ����ϣ�Ȼ�������Ĵ������ջء�\n";
                break;

        default:
                msg = "�㻺���������ɣ���������ˮ¶����Ϊ���á�\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_outing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ�˱չء�\n");
        message_vision(HIY "$N" HIY "����̾��һ�����������������ۡ�\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "�չ���;ͻȻ������");
        return 1;
}

protected void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : animaout

�����ͨ�ζ������Ժ󣬲��Ҿ��зǳ�����ľ�������ʱ����������
��ָ������ԪӤ����������ɹ����Դ���������ľ��;������ޡ�

HELP );
        return 1;
}
