// This program is a part of NITAN MudLIB
// fuxue.c �黨ָ ���黨��Ѩ��

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�黨��Ѩ"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�黨��Ѩֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("���ڹ���򲻹�������ʹ���黨��Ѩ��\n");

        if ((int)me->query_skill("finger") < 150)
                return notify_fail("���ָ����Ϊ������Ŀǰ������ʹ���黨��Ѩ������\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʹ���黨��Ѩ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (me->query_skill_mapped("finger") != "nianhua-zhi")
                return notify_fail("��û�м����黨ָ���޷�ʹ���黨��Ѩ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʹ���黨ָ�������黨��Ѩ������ס��$n"
              HIY "��ȫ��ָ���������Ĺ���$p" HIY "��ҪѨ��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIG "���$p" HIG "��$P" HIG "���˸����ֲ�����\n" NOR;
                if (! target->is_busy())
                        target->start_busy(ap/120 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        }
        else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ʽ����æԾ�����ܿ���$P"
                       CYN "�Ĺ�����\n" NOR;
                addn("neili", -30, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
