// chan.c ��糾�� ���־�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("qiufeng-chenfa", 1) < 80)
                return notify_fail("����糾������Ϊ����������ʹ�ò��־���\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        msg = CYN "$N" CYN "ʹ����糾���������־�������������ͼ��$n"
              CYN "��ȫ���ס��\n" NOR;

        me->start_busy(random(1));
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                msg += CYN "���$p" CYN "��$P" CYN "���˸����ֲ�����\n" NOR;
                target->start_busy( (int)me->query_skill("whip") / 28 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����û���ϵ���\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}