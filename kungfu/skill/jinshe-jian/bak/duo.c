// This program is a part of NITAN MudLIB
// duo.c  ���߽���  (����)

#include <ansi.h>
inherit F_SSERVER;

void end(object target, int damage);

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() )
                return notify_fail("����ֻ�ܶ�ͬ�ط��Ķ���ʹ�á�\n");
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 100 )
                return notify_fail("��Ľ��߽���������죬����ʹ�á����ǡ���\n");
                
        if( query("neili", me)<200 )
                return notify_fail("����������̫��������ʹ�����ǡ�\n");
                
        if( query_temp("sword", target) == 1 )
                return notify_fail(query("name", target)+"���ڻ����ɢ�䣬����ֹ�����!\n");
                
        msg = HIW "$NͻȻ���н�â��ʢ��һ�ɺ����ƿ�ֱϮ$n��\n"NOR;
        addn("neili", -400, me);
        me->start_busy(1);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("dodge")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += WHT"$p���ŵû����ɢ��ֻ���Է����ƴ�ʢ��ԽսԽ�¡�\n"NOR;
                if (! target->is_busy())
                target->start_busy(3);
                addn("neili", -100, me);
                damage = me->query_skill("jinshe-jian",1);
                damage = 0-damage/8-random(damage/8);
                
                if( !query_temp("apply/attack", target) )
                    set_temp("apply/attack", damage, target);
                else
                    addn_temp("apply/attack", damage, target);
                if( !query_temp("apply/defense", target) )
                    set_temp("apply/defense", damage, target);
                else
                    addn_temp("apply/defense", damage, target);
                set_temp("sword", 1, target);
                call_out("end", 30, target, damage);
        }
        else
        {
                msg += HIY"$p����Ӧս��û���ܵ������ǡ�������Ӱ�죡\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

void end(object target,int damage)
{
        if (! objectp(target)) return;
        delete_temp("sword", target);
        addn_temp("apply/attack", 0-damage, target);
        addn_temp("apply/defense", 0-damage, target);
        message_vision(RED"$N���ڴӶ��ǵ���Ӱ��ָ��˳�����\n"NOR,target);
}

