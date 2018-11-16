// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "���־�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((level = me->query_skill("quanzhen-jian", 1)) < 80)
                return notify_fail("��ȫ�潣��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ʹ��ȫ�潣���������־���" + weapon->name() +
              HIC "�������������������˷�������$n" HIC "��\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$p" HIR "ֻ����$P" HIR
                       "����ѹ��һ��ǿ��һ�㣬ֻ��ʹ����������˹��ֵ���\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "$p" CYN "��$P" CYN "�з��Ͻ������²���С��"
                       "��������$P" CYN "�����У���¶���������\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
