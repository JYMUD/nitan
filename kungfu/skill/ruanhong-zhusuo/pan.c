// panying.c ��ӥ��

#include <ansi.h>
#include <combat.h>

string name() { return YEL "��ӥ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 80)
                return notify_fail("����������������죬�޷�ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("��û�м�������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = YEL "$N" YEL "ʹ�������������ӥ��������������һ������ʱ��"
              "Ӱ���أ���ȫ����$n" YEL "���ܣ�\n";

        me->start_busy(1);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "΢�����죬һʱ���Ʋ�͸$N" HIR "����"
                       "����ٱ����˸����ֲ�����\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ��С��Ӧ�ԣ���û���ϵ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}