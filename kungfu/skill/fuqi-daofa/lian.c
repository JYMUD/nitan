// lian.c�����޵������У����಻��
// By Alf, Last Update 2001.05

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ����һ���С�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("fuqi-daofa", 1) < 40 )
                return notify_fail("����Ŀǰ�Ĺ�������ʹ������һ���С�\n");

        if( random(query("combat_exp", me))>query("combat_exp", target)/20 )
        {
                attack_time = random((int)me->query_skill("fuqi-daofa", 1) / 20);
                if(attack_time < 1)
                        attack_time = 1;

        msg = HIC "$N��ȻһЦ��������Ȼ�ӿ죬������β���Σ����಻���Ĺ���$n��\n" NOR;
        msg += HIM "$n��������ʽ��·����ʱ��æ���ң��ֵ�������˲���ѽ������У�\n" NOR;

                for(i = 0; i < attack_time; i++)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                message_combatd(msg, me, target);
                me->start_busy(3);
                addn("neili", -100, me);
        }

        else
        {
        msg = HIC "$N��ȻһЦ��������Ȼ�ӿ죬������β���Σ����಻���Ĺ���$n��\n" NOR;
        msg += HIY"����$n���з��������в��У�������ˮ�ò�����������һһ���⡣\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(3);
        }

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

