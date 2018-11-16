
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��ջ���" NOR; }

int perform(object me, string skill, string arg)
{
        int add_dam;      	

        if (me->query_temp("special/jingang"))
                return notify_fail("��ջ��弼���Ѿ���ʩչ���ˡ�\n");

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIY "$N" HIY "˫ȭ�ӳ������һ������Ȼ��ȫ�������֣�Ƥ���������һ�����һ�� ����\n" NOR, me);
 
        me->start_busy(1);

        me->set_temp("special/jingang", 1);
	me->add_temp("apply/armor", 500);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, 500 :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/jingang"))
        {
		me->add_temp("apply/armor", -500);
	        me->delete_temp("special/jingang");
	        tell_object(me, "���ջ����ؼ�ʩչ��ϡ�\n");
        }
}

