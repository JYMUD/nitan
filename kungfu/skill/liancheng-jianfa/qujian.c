// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "ȥ����"; }

int perform(object me, object target)
{
        object weapon;
        object obj;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() )
                return notify_fail("ȥ����ֻ�ܶԶ���ʹ�á�\n");

        if( me->query_skill("liancheng-jianfa") < 80 )
                return notify_fail("������ǽ���������죬����ʩ��ȥ���ơ�\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("���ֲ�û��ʹ��������\n");

        msg = "$N��Хһ������ֱ���еı��У������ǽ�����ȥ����˳�ƴ�����$n�ı�����\n";

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIY "ֻ����һ���������֮�������$p�ı��б�$P���еı���һ��һ����ԶԶ�ط��˿�ȥ��\n" NOR;
                obj=query_temp("weapon", target);
                obj->unequip();
                obj->move(environment(me));

                target->start_busy(1 + random(4));
        } else
        {
                msg += "����$p������$P����ͼ����û���ϵ���\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}