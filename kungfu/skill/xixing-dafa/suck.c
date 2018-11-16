// suck.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;
        int amount;
        object weapon;

        if (! target || target == me) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if (! objectp(target) || ! me->is_fighting(target))
                return notify_fail("��ֻ����ȡս���еĶ��ֵĵ�Ԫ��\n");

        if( query("race", target) != "����" || 
            query("not_living", target) )
                return notify_fail("����ˣ�ֻ�л��ŵ���������е�Ԫ��\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ����Ԫ��\n");

        if (! me->is_fighting() || ! target->is_fighting())

        if ((int)me->query_skill("xixing-dafa", 1) < 100)
                return notify_fail("������Ǵ���δ��ɣ���"
                                   "������ȡ�Է��ĵ�Ԫ��Ϊ���ã�\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������ʹ�����Ǵ󷨡�\n");

        if ((int)me->query_current_neili_limit() <= my_max)
                return notify_fail("����ڹ�ˮƽ���ޣ�����ȡҲ��ͽ�͡�\n");

        if( query("max_neili", target)<100 )
                return notify_fail( target->name() +
                        "��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

        if( query("max_neili", target)<query("max_neili", me)/5 )
                return notify_fail( target->name() +
                        "���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                message_combatd(HIR "$N" HIR "̽�����֣�ƽƽ������$n"
                                HIR "����ǰ���ƺ�û�а��������\n\n" NOR,
                                me, target);
        else
                message_combatd(HIR "$N" HIR "�����е�" + weapon->name() +
                                HIR "һ������ı���$n" HIR + "��$p"
                                HIR "��æ��ס��\n" NOR,
                                me, target);

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

                amount = 1 + (me->query_skill("xixing-dafa", 1) - 100) / 10;
                addn("max_neili", -amount, target);
                addn("max_neili", amount, me);
                addn("exception/xixing-count", amount*10, me);
                SKILL_D("xixing-dafa")->check_count(me);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);

                me->start_busy(5);
                target->start_busy(random(5));
                addn("neili", -10, me);

                call_out("del_sucked", 10, me);
        } else
        {        
                message_combatd(HIY "����$p" HIY "������$P" HIY
                                "����ͼ��������������$P" HIY
                                "���漴���˿�ȥ��\n" NOR,
                                me, target);
                me->start_busy(5);
                call_out("del_sucked", 15, me);
        }

        return 1;
}

void del_sucked(object me)
{
        delete_temp("sucked", me);
}