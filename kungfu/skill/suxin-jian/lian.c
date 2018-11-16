#include <ansi.h>

#define LIAN "��" HIW "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;
 
        if( userp(me) && !query("can_perform/suxin-jian/lian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" LIAN "��\n");

        if ((int)me->query_skill("suxin-jian", 1) < 120)
                return notify_fail("����Ů���Ľ�������죬����ʩչ" LIAN "��\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" LIAN "��\n");

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail("��û�м�����Ů���Ľ�������ʩչ" LIAN "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" LIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n$N" HIM "��������һת����ʱ��$n" HIM "���������������п�"
             "�Ƽ򵥣���ȴѸ�ͷǳ������˷�����˼��" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg = HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                      HIR "��æ�мܣ����нпࡣ\n" NOR;
                count = ap / 8;
                attack_time += random(ap / 40);
                addn_temp("apply/attack", count*2, me);
        } else
        {
                msg = HIC "$n" HIC "��$N" HIC "�⼸����ʽ������������"
                      "����ֻ�ÿ���мܡ�\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 20, 20);
        }
        addn_temp("apply/attack", -count*2, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}