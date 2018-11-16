// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����ʽ"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("liancheng-jianfa", 1) < 70 )
                return notify_fail("������ǽ���������죬����ʹ�á�\n");

        if( (int)me->query_skill("force", 1) < 70 )
                return notify_fail("��Ļ����ڹ������ߡ�\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á�����ʽ����\n");

        msg = HBYEL "ֻ��$N���б��������ֿ��ٽ��������֣����������벻���ķ�λ����$n�����ա�\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           CYN "$nֻ��ֻ��������һ������������ʹ��"
                                           "�ѱ�$N�����Ĵ���һ���⣡\n" NOR);

                addn("neili", -200, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p����һ��,�����$P���Ʒ硣\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
