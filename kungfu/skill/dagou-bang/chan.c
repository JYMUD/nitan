// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���־�" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 60)
                return notify_fail("��򹷰���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "ʹ���򹷰�����" HIC "��" HIG "���־�����ͷ��"
              "�������㣬���಻��������$n" HIG "��С�Ⱥͽ��ס�\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "��Ӱ�ܶ���$n" HIR "��ʽ��Ȼһ�����ѱ�$N"
                       HIR "���ı�����ͣ����æ���ң�\n" NOR;
                target->start_busy(4 + random(level/60));
                me->start_busy(1);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ���򶨽��У�һ˿���ҡ�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
