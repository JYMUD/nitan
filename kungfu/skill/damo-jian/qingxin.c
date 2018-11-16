// This program is a part of NITAN MudLIB
// qingxin.c �����Ľ���

#include <ansi.h>

inherit F_SSERVER;
string name() { return "���Ľ�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int ainc, dinc;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����Ľ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("damo-jian", 1) < 200)
                return notify_fail("��Ĵ�Ħ����������죬����ʹ�á����Ľ�����\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������޷�ʹ�á����Ľ�����\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("��û�м�����Ħ�������޷�ʹ�á����Ľ�����\n");

        if( query_temp("damo_qingxin", target) )
                return notify_fail("�Է��ող��й���Ħ���Ľ����㲻������һ���ˡ�\n");

        msg = HIM "$N" HIM "��" + weapon->name() + "����һ����һ��"
              "������Ȼ������������·����$n" HIM "��\n" NOR;

        addn("neili", -200, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if( !query_temp("powerup", target) )
        {
                msg += CYN "����$p" CYN "�����ƺ���û��������������" CYN
                       "ս����$P" CYN "��һ��û�����κ����á�\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "���û���һ�飬������"
                       "��ľ�Ȼʹ����һ��������\n" NOR;
                ainc=query_temp("apply/attack", target);
                dinc=query_temp("apply/defense", target);
                addn_temp("apply/attack", -ainc, target);
                addn_temp("apply/defense", -dinc, target);
                set_temp("damo_qingxin", 1, target);
                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                   target, ainc, dinc:), ap / 5);
        } else
        {
                msg += CYN "����$p" CYN "�������ʹ��$P" CYN
                       "��һ��û�����κ����á�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

void remove_effect(object me, int ainc, int dinc)
{
        if (! objectp(me))
                return;

        if( query_temp("damo_qingxin", me) )
        {
                delete_temp("damo_qingxin", me);
                addn_temp("apply/attack", ainc, me);
                addn_temp("apply/defense", dinc, me);
                tell_object(me, "����������ָ���һЩ��\n");
        }
}