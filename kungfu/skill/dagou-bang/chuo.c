// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���־�" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 100)
                return notify_fail("��򹷰���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "ʹ���򹷰�����" HIR "��" HIG "���־�����"
              "��һ����ʱ��Ӱ�ܶ�������$n" HIG "��ǰҪѨ��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "ȫȻ�޷�����$N" HIR "��"
                                           "������ʽ���ؿ�һ�飬���һ����Ѫ��\n" NOR);
                me->start_busy(2);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "��$n" CYN "ȫ���������¶���������ʹ��$N"
                       CYN "�����޹�������\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
