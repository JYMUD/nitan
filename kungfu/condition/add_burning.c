
// add_burning.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	if( !living(me) )
	{
	        set_temp("die_reason", "���˶���", me);
		message("vision", me->name() + "���������ʹ��غ���һ����\n", environment(me), me);
	}
	else
	{
		tell_object(me, HIR "��ֻ���Լ������ڻ�ɽ֮�У����忪ʼ��ȼ����Ѫ��������ʼ��ͣ���½�����\n" NOR );
	}
	
	me->receive_damage("qi", 2000);
	me->receive_wound("qi", 1000);
        addn("neili", -1000, me);
        if( query("neili", me) < 0 )
                set("neili", 0, me);

	me->apply_condition("add_burning", duration - 1);

	if( duration < 1 ) return 0;
	return CND_CONTINUE;
}

int dispel(object me, object ob, mapping cnd)
{
        return 0;
}

string query_type(object me)
{
	return "poison";
}

