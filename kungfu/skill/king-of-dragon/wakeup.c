// wakeup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( (!target) || query("id", target) == query("id", me) )
                return notify_fail("你要用真气救醒谁？\n");
/*
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功救人！\n");
*/
        if(target == me)
                return notify_fail("你不能为自己救醒自己！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "已经受伤过重，经受不起你的真气震荡！\n");

        message_combatd(HIY "$N坐了下来运起内功，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n\n过了不久，$N额头上冒出豆大的汗珠，$n吐出一口瘀血，脸色看起来红润多了。\n$n慢慢的苏醒过来。\n" NOR, me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target))set("qi",query("eff_qi",  target), target);

           target->remove_call_out("revive");
           target->revive();
           target->reincarnate();
 
        addn("neili", -150, me);
        set("jiali", 0, me);
//                me->start_busy(5);
//                target->start_busy(5);
        return 1;
}