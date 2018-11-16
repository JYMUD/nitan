// This program is a part of NITAN MudLIB
// zhui.c  ׷��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg, pmsg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��׷����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 150 )
                return notify_fail("��Ľ��߽���������죬����ʹ�á�\n");
                                
        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á�׷������\n");
                        
        msg = HIY "$N΢΢һЦ�������������ޣ�$nȴ�е�Ī���ѹ����\n"NOR;

        me->want_kill(target);
        if( !target->is_killing(me) ) 
                target->kill_ob(me);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                target->start_busy( random(2) + 2);
                
                damage = damage_power(me, "sword");
                
                addn("neili", -400, me);
                pmsg = HIR "ֻ��$N�����˸�����Ļ��ߣ��Ӳ���˼��ĽǶ���$nɱȥ,\n$nֻ���ñ���һ������������ؿ���ǰ�صĽ��⣡\n" NOR;
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65, pmsg);
                me->start_busy(2);
        } else 
        {
                msg += CYN"����$p�͵���ǰһԾ,������$P�Ĺ�����Χ��\n"NOR;
                addn("neili", -200, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
