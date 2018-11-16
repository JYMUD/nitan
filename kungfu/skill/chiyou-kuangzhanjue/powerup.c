// powerup.c 

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用蚩尤狂战决来提升自己的战斗力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        
        message_combatd(HIY "$N" HIY "深吸一口气，待到呼出之时，双目已经射出赤红的光芒，周围的空气中弥漫着阵阵的战意！\n" NOR, me);
        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/defense", skill/2, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                           skill / 2:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的蚩尤狂战决运行完毕，将内力收回丹田。\n");
        }
}
