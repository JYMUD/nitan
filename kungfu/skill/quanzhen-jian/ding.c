// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "������" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 100)
                return notify_fail("��ȫ�潣��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("����������̫��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "�������Ҽ�����������������������һʽ��"
              HIR "������" NOR + HIC "��бб�̳���\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "����$N" HIR "������ǧ��"
                                           "��һ��������֪����мܣ���ʱ�����ش�"
                                           "��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ��бԾ�ܿ���\n" NOR;
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}