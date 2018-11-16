#include <ansi.h>
#include <combat.h>

string name() { return HIG "��ָ��ɽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("zhongnan-zhi", 1) < 60)
                return notify_fail("������ָ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "zhongnan-zhi")
                return notify_fail("��û�м�������ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "zhongnan-zhi")
                return notify_fail("��û��׼������ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<60 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "ббһָ�̳���ָ��ζ����ѣ�ңң����$n"
              HIG "ҪѨ���ڡ�\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -60, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "�м�ʧ�󣬱�$P" HIR
                                           "��һָ���˸����ţ���Ϣ��ʱһ�ͣ���Ѫ������\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -20, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}