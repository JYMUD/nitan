// This program is a part of NITAN MudLIB
// fugu.c ��������

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "��������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if ((int)me->query_skill("tianshan-zhang", 1) < 60)
                return notify_fail("�����ɽ�ȷ�������죬����ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("��û�м�����ɽ�ȷ���ʹ����" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "�����Ц�����е�" + weapon->name() +
              HIG "����Ӱ��һ��Ϯ��$n��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "���$n" HIR "��$N" HIR "�ŵþ���ʧ�룬"
                       "һʱ����æ���ң�����Ӧ�ԣ�\n" NOR;

                target->start_busy(ap/100 + 2);
        } else
        {
                msg += "����$n" HIR "������$N" HIR "����ͼ��"
                       "����һ�ˣ���ȥ��$N" HIR "��׷����\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
