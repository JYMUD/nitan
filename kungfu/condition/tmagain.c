// tmagain.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        
        me->apply_condition("tmagain", duration - 1);

        if (duration == 1)
        {
                me->apply_condition("jobshadi_failed", 0);
                return 0;
        }

        return CND_CONTINUE;      
}
