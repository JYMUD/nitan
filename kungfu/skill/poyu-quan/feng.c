// This program is a part of NITAN MudLIB
// feng.c ����ȭ������֡�

#include <ansi.h>

string name() { return HIG "�����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if ((int)me->query_skill("poyu-quan", 1) < 60)
                return notify_fail("�����ʯ����ȭ������죬����ʹ��" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan")
                return notify_fail("��û��׼��ʹ����ʯ����ȭ���޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<80 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "\nֻ��$N" HIC "������̽����ȭ쬵�һ�����Ʒ���\n"
              "�ʹ�������������ʯ����ȭ���ľ���֮һ��" HIG "�����" HIC "����\n" NOR;

        addn("neili", -40, me);
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "�����мܣ�һʱȴ����"
                       "�������ã���$P" HIR "��ס����һ������ʱ����"
                       "���ȣ��������������Ȧ�ӡ�\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "����һ�ܣ�Ӳ��������$P"
                       CYN "��һȭ��\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
