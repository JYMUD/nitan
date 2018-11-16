// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "�տ���Ҳ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("kongming-quan", 1) < 150)
                return notify_fail("��Ŀ���ȭ������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("��û�м�������ȭ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("��û��׼������ȭ������ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����ڵ�����̫��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "ʹ������ȭ��" HIG "�տ���Ҳ" NOR + WHT "����ȭ��"
              "����ʵʵ���仯Ī�⣬��$n" WHT "һʱ���Բ�׽��\n" NOR;
        addn("neili", -80, me);

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "unarmed");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "�޷�����$N" HIR "ȭ�а�"
                                           "�أ�����һȭ����Ҫ������ʱŻ��һ���"
                                           "��Ѫ��\n:����@?");
        } else
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��ȭ���еı仯������Ӧ�ԣ���û�гԿ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
