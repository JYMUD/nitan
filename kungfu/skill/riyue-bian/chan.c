// This program is a part of NITAN MudLIB
// chan.c

#include <ansi.h>

inherit F_SSERVER;
string name() { return "���ƾ�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��û�����ű��ӡ�\n");

        if( query("neili", me)<80 )
                return notify_fail("�����������������޷�ʩչ�����ơ�����\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷����޷�ʩչ�����ơ�����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ʹ�����±޷������ơ���������������ͼ��$n"
              HIC "��ȫ�����������\n";

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR "���˸����ֲ�����\n" NOR;
                target->start_busy(ap/80 +2);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ��С��Ӧ�ԣ���û���ϵ���\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
