// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return WHT "��ȭ���" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("hujia-quan", 1) < 80)
                return notify_fail("��ĺ���ȭ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "hujia-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "hujia-quan")
                return notify_fail("��û��׼������ȭ��������ʩչ" + name() + "��\n");

        if( query("neili", me)<80 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "�ݲ���ǰ��ȭ�е��������籼�ף���ʱ����$n" WHT "������ȭ��\n" NOR;

        addn("neili", -40, me);
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$n" HIR "�޷�����$N" HIR "��ʽ�е���ʵ��"
                       "������æ���ҡ�\n" NOR;
                target->start_busy(ap / 120 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "�����У�����һ����"
                       "�ܿ�����������ȭӰ��\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
