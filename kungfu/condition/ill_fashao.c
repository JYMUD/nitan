// ill_fashao.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_fashao"; }

int min_qi_needed() { return 10; }

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;

        message("vision", HIG + me->name() + "的臉蛋燒得"
                          "通紅，看來是發高燒了。\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 1 ) {
                me->set_temp("die_reason", "發燒太重，活活被折磨死了");
                me->die();
                return 0;
        }
        else
                tell_object(me, HIB "你的臉蛋燒得通紅，看來是發高燒了。\n" NOR );

        me->receive_wound("qi", 1);
        me->receive_damage("qi", 1);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}
