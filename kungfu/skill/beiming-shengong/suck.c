// maxsuck.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;
        int sucked;

        if (! target || target == me) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if (! objectp(target) || ! me->is_fighting(target))
                return notify_fail("��Ҫ��ȡ˭�ĵ�Ԫ��\n");

        if( query("race", target) != "����" || 
            query("not_living", target) )
                return notify_fail("����ˣ�ֻ�л��ŵ���������е�Ԫ��\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ����Ԫ��\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʩ�ñ�ڤ�����˵�Ԫ��\n");

        if (! me->is_fighting() || ! target->is_fighting())

        if ((int)me->query_skill("beiming-shengong", 1) < 90)
                return notify_fail("��ı�ڤ�񹦹���������������ȡ�Է��ĵ�Ԫ���\n");

        if( query("neili", me)<20 )
                return notify_fail("�����������������ʹ�ñ�ڤ�񹦡�\n");

        if ((int)me->query_current_neili_limit() <= my_max)
                return notify_fail("����ڹ�ˮƽ���ޣ�����ȡҲ��ͽ�͡�\n");

        if( query("max_neili", target)<100 )
                return notify_fail( target->name() +
                        "��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

        if( query("max_neili", target)<query("max_neili", me)/5 )
                return notify_fail( target->name() +
                        "���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

        message_combatd(HIG "$N" HIG "ȫ��һ��������֣���������$n"
                        HIG "���ֱ��ϡ�\n\n" NOR, me, target);

        if (living(target) && !target->is_killing(me))
        {
                me->want_kill(target);
                target->kill_ob(me);
        }

        sp = me->query_skill("force");
        dp = target->query_skill("force");

        set_temp("sucked", 1, me);

        if ((sp + random(sp) > dp + random(dp) ) || ! living(target))
        {
                tell_object(target, HIR "��ֻ��ȫ������ȫ������"
                            "��ѩ����ʧ����Ӱ���٣�\n" NOR);
                tell_object(me, HIG "�����" + target->name() +
                            HIG "�ĵ�Ԫ������ԴԴ���������˽�����\n" NOR);

                sucked = 1 + (me->query_skill("beiming-shengong", 1) - 90) / 10;
                addn("max_neili", -sucked, target);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);
                if (my_max > tg_max + 100)  sucked /= 2;
                if (my_max > tg_max + 200)  sucked /= 2;
                if (my_max > tg_max + 400)  sucked /= 2;
                if (my_max > tg_max + 800)  sucked /= 2;
                if (my_max > tg_max + 1600) sucked /= 2;
                if (my_max > tg_max + 3200) sucked /= 2;

                if (sucked < 1)
                        tell_object(me, HIG "�����㷢�ֶԷ�����"
                                    "�ƺ�������̫�࣬һʱ����������Ϊ���á�\n" NOR);
                else
                        addn("max_neili", sucked, me);

                me->start_busy(7);
                target->start_busy(random(7));
                addn("neili", -10, me);

                call_out("del_sucked", 10, me);
        }
        else
        {       
                message_combatd(HIY "����$p" HIY "������$P" HIY
                                "����ͼ����������˿�ȥ��\n" NOR,
                                me, target);
                me->start_busy(7);
                call_out("del_sucked", 20, me);
        }

        return 1;
}

void del_sucked(object me)
{
        delete_temp("sucked", me);
}