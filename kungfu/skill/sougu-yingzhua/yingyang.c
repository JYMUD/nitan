// muyeyingyang.c ��Ұӥ��

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��Ұӥ��"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ұӥ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( query_temp("weapon", me) )
                return notify_fail("�ѹ�ӥצ��������ַ���ʩչ��\n");

        if ((int)me->query_str() < 30)
                return notify_fail("���������,����ʹ����Ұӥ�\n");

        if ((int)me->query_skill("sougu-yingzhua",1) < 150)
                return notify_fail("����ѹ�ӥצ����Ϊ����,Ŀǰ������ʹ����Ұӥ�\n");

        if ((int)query("neili", me) < 800)
                return notify_fail("���������ڲ���, ����ʹ����Ұӥ�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if ( !living(target))
                return notify_fail("�Է��Ѿ������ˣ��ŵ������ɣ�\n");

        msg = HIY "$N" HIY "ʹ���ѹ�ӥצ����������Ұӥ���˫צ���ץ��$n"
              HIY "��ȫ��ҪѨ��\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR "����ҪѨ����ʱ�������ã�\n" NOR;
                target->start_busy( (int)me->query_skill("sougu-yingzhua",1) / 120 + 1);
                addn("neili", -150, me);
        } else
        {
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ����û���ϵ���\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}