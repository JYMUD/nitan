#include <ansi.h>
#include <combat.h>

string name() { return HIW "�����ܾ�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("ֻ�п��ֲ���ʩչ" + name() + "��\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 60)
                return notify_fail("�������ȭ��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("������û��׼��ʹ������ȭ��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "ֻ��$N" HIW "һ���Ϻȣ�˫ȭ�����뷢��һʽ�������ܾ���Я"
              "�ŷ���֮�ƺ���$n" HIW "��\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "���$p" HIR "���ܲ�������$P" HIR
                                           "һȭ�������ţ���ʱ������Ѫ����������"
                                           "��\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}