// This program is a part of NITAN MudLIB
// chan.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "���־�" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 80)
                return notify_fail("�������������Ϊ����������ʹ�ò��־���\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        msg = CYN "$N" CYN "ʹ���������塸�����־�������������ͼ��$n"
              CYN "��ȫ���ס��\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += CYN "���$p" CYN "��$P" CYN "���˸����ֲ�����\n" NOR;
                target->start_busy( me->query_skill("whip", 1) / 100 + 2 );
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����û���ϵ���\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}