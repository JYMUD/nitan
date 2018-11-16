// xiezi_poison.c
#include <ansi.h>

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        if( duration < 1 ) return 0;
        me->receive_wound("qi", 15+random(10), "蝎子毒发作");
        me->receive_damage("jing", 25+random(20), "蝎子毒发作");
        tell_object(me, HIG"你感到呼吸困难，四肢渐渐肿了起来。你中的蝎子毒发作了！\n" NOR );
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("xiezi_poison", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "poison";
}