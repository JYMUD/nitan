#include <ansi.h>

string name() { return HIG "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((level = me->query_skill("kongming-quan", 1)) < 100)
                return notify_fail("��Ŀ���ȭ������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("��û�м�������ȭ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("��û��׼������ȭ������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ�����̫��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "ʹ������ȭ��" HIG "��������" NOR + WHT "����˫��"
              "���²�������ת���⣬��ͼ����$n" WHT "�Ĺ��ơ�\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "���$n" HIR "��$N" HIR "��ȭ����ǣ�ƣ��м�"
                       "������ȫȻ�޷�������\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ������"
                       "�㣬ȫ��Ӧ�����硣\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
