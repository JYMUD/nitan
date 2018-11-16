// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "�����ת" NOR; }

inherit F_SSERVER;

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

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("taiji-jian", 1) < 160)
                return notify_fail("���̫������������죬����ʩչ" + name() + "��\n");

        if( query("neili", me)<250 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����Х������" + weapon->name() +
              HIW "��������������һ����ԲȦ����$n" HIW "Ȧ�ڵ�"
              "�С�\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap*4/3) > dp)
        {
                msg += HIY "���$p" HIY "��$P" HIY
                       "���˸����ֲ������������˲�Ͼ��\n" NOR;
                count = ap / 10;

                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "�⼸����������"
                       "�����Ҵ��⣬С��Ӧ����\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
