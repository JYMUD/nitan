// anqi_poison.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( duration < 1 ) return 0;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", me->name() + "ʹ��غ���һ����\n", environment(me), me);
        }
        else
        {
                tell_object(me, HIB"��Ȼһ���ʹϮ�������а������˿ڶ��ˣ�\n"NOR );
                message("vision", me->name() + "������ͻȻ¶��ʹ�����飬����ҧ�ø��ֱ�졣\n", environment(me), me);
        }
        me->receive_wound("qi",15 + random(10),"������������");
        me->receive_wound("jing", 10,"������������");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("anqi_poison", duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}