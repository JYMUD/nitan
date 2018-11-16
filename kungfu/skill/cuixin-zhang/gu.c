// This program is a part of NITAN MudLIB
// gu.c ��עһ��

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��עһ��"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("����עһ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á���עһ������\n");

        if( (int)me->query_skill("cuixin-zhang", 1) < 60 )
                return notify_fail("��Ĵ����Ʋ�����죬����ʹ�á���עһ����!\n");

        if (me->query_skill_mapped("strike") != "cuixin-zhang")
                return notify_fail("��û��׼��ʹ�ô����ƣ��޷�ʩչ��"RED"��עһ��"CYN"����\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á���עһ����!\n");

        msg = CYN "$NĬ���񹦣�ʹ����"RED"��עһ��"CYN"����˫��ƽ�ƹ���$n��\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                me->start_busy(random(2));
                if (! target->is_busy())
                        target->start_busy(random(3));

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                addn("neili", -damage/3, me);

                if( damage < 40 )
                        msg += HIY"���$n��$N˫�ƴ����ؿڣ��ƺ�һ����\n"NOR;
                else if( damage < 80 )
                        msg += HIY"���$n��$N��˫�ƴ����ؿڣ����١���һ������������\n"NOR;
                else if( damage < 160 )
                        msg += RED"���$n��$N��˫�ƴ����ؿڣ������ܵ�һ���ش�����������������\n"NOR;
                else
                        msg += HIR"���$n��$N��˫�ƴ����ؿڣ���ǰһ�ڣ���һ������һ���ɳ�ȥ�ü���Զ��\n"NOR;

        }
        else
        {
                me->start_busy(1 + random(2));
                msg += CYN"����$p������$P����ͼ������һת�����ƻػ���\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
