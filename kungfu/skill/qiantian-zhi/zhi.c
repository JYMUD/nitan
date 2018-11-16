// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "Ǭ����ָ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("qiantian-zhi", 1) < 80)
                return notify_fail("��Ǭ��ָ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "qiantian-zhi")
                return notify_fail("��û�м���Ǭ��ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "qiantian-zhi")
                return notify_fail("��û��׼��Ǭ��ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "��Ȼʹ��һ�С�Ǭ����ָ����˫ָ��ʩ��ͬʱ��$n"
              HIR "���ż��ؿڴ���ȥ��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "������������ʱ��$P"
                                           HIR "һָ���У���Ϣ���ɵ�һ�ͣ�����֮����\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}