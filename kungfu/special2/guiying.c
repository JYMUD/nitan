
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��Ӱ����" NOR; }

int perform(object me, string skill, string arg)
{
	int add_dam;

        if (me->query_temp("special/guiying"))
                return notify_fail("��Ӱ���Ǽ����Ѿ���ʩչ���ˡ�\n");

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIY "$N" HIY "�������������������ͬʱ�߶����ظ���������תһ�����죬ɲʱ�����Ʈ���ޱ� ����\n" NOR, me);
 
        me->start_busy(1);

	add_dam = 1 + me->query_skill("dodge") * 2 / 25;
	
        me->set_temp("special/guiying", 1);
	me->add_temp("apply/dodge", add_dam);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, add_dam :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/guiying"))
        {
		me->add_temp("apply/dodge", -1 * add_dam);
	        me->delete_temp("special/guiying");
	        tell_object(me, "���Ӱ���Ǽ�ʩչ��ϡ�\n");
        }
}

