#include <ansi.h>
#include <combat.h>

string name() { return HIG "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("canglang-zhi", 1) < 80)
                return notify_fail("�����ָ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "canglang-zhi")
                return notify_fail("��û�м�������ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "canglang-zhi")
                return notify_fail("��û��׼������ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "��Ȼʩ��һ�ơ��������졹��ʮָ�׷���ָ����Ȼ��"
              "�죬ȫȫ����$n" HIG "��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "���$n" HIR "������������$N" HIR
                                           "һָ���У�ȫ����Ѫ���ڲ��ѡ�\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "����$n" CYN "ʶ����$N"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}