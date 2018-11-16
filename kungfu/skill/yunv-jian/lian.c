// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "��������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("yunv-jian", 1) < 120)
                return notify_fail("����Ů����������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("��û�м�����Ů����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n$N" HIM "��������һת����ʱ��$n" HIM "���������������п�"
             "�Ƽ򵥣���ȴѸ�ͷǳ������˷�����˼��" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                      HIR "��æ�мܣ����нпࡣ\n" NOR;
                count = ap / 8;
                attack_time += random(ap / 40);
                addn_temp("apply/attack", count, me);
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
        me->start_busy(1 + random(3));

        return 1;
}