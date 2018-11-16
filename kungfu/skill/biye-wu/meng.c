// This program is a part of NITAN MudLIB
// meng.c ��Ҷ����衸���Ρ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;        

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�����Ρ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á����Ρ���\n");           

        if( (int)me->query_skill("biye-wu", 1) < 40 )
                return notify_fail("��ı�Ҷ����費����죬����ʹ�á����Ρ���\n");

        if( (int)me->query_skill("biyun-xinfa", 1) < 30 )
                return notify_fail("��ı����ķ������ߣ��������������˵С�\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á����Ρ���\n");

        msg = CYN "$NĬ��ھ���ʹ����Ҷ�����֮�����Ρ�����������������$n��\n"NOR;

        
        ap = attack_power(me, "force");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                //me->start_busy(3);
                //target->start_busy(random(3));
                
                damage = damage_power(me, "force");
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/6);
                addn("neili", -damage/3, me);
                
                if( damage < 20 )
                        msg += HIY"���$n�ܵ�$N�����������ƺ�һ��������ȥ����ƣ����\n"NOR;
                else if( damage < 40 )
                        msg += HIY"���$n��$N����������ֻ�������з��ƣ�ֻ��ú���Ϣ��Ϣ��\n"NOR;
                else if( damage < 80 )
                        msg += RED"���$n��$N������һ�������������죬��ʶ��ʼģ��������\n"NOR;
                else
                        msg += HIR"���$n��$N������һ����ǰһ�ڣ����㵹���ۿ���Ҫ���������ˣ�\n"NOR;
                
        }
        else 
        {
                me->start_busy(4);
                msg += CYN"����$p������$P����ͼ����û���ϵ���\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
