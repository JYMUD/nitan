#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "���ָѨ" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("���ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("tiangang-zhi") < 100)
                return notify_fail("������ָѨ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("����������ڲ���������ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (me->query_skill_mapped("finger") != "tiangang-zhi")
                return notify_fail("��û�м������ָѨ��������ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ʹ�����ָѨ�����������ָѨ��������"
              "һ����ָ����$n" HIC "��ǰ��Ѩ����������\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "�������У�ƴ�����$P"
                       HIR "ָ����ʱ�������ң�\n" NOR;
                target->start_busy((int)me->query_skill("tiangang-zhi", 1) / 100 + 2);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "$p" CYN "�鼱����������һԾ���˳���Զ��\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
