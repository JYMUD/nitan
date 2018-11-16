#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "��������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((level=me->query_skill("sanwu-shou", 1)) < 100)
                return notify_fail("�����������ֲ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("��û�м������������֣�����ʩչ" + name() + "��\n");

        if( query("neili", me)<140 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n$N" HIM "��Хһ�����ڿն���ʩ������ ��" HIW "��"
              "������" HIM "����\n����" + weapon->name() + HIM "��������"
              "��㣬�������컨�������$nȫ�����" HIM "��" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                      HIR "��æ�мܣ����нпࡣ\n" NOR;
                count = level / 5;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg= HIC "$n" HIC "��$N" HIC "�⼸����ʽ������������"
                     "����ֻ�ÿ���мܡ�\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));

        return 1;
}