
#include <ansi.h>

//inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "����Ұ��" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
      
	joblv = me->query_joblv();

        if (me->query_temp("special2/xianyun"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

	if (me->query("yhjob/job") != "��ʿ")
		return notify_fail("���ְҵ�����޷�ʩչ��\n");
		
	if (me->query("neili") < 600)
		return notify_fail("����������㣬�޷�ʩչ��\n");

	if (joblv < 10)
		return notify_fail("���ְҵ�ȼ����㣬�޷�ʩչ��\n");		

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIM "$N" HIM "ʩչ������Ұ�ף���ʱƮ�����磬����֮����\n" NOR, me);
 
        me->add("neili", -600);
        me->start_busy(1);

	joblv = joblv + me->query("lhpoint/special/xianyun") * 8;

        me->set_temp("special2/xianyun/joblv", joblv);
	me->add_temp("apply/defense", joblv * 10);
	me->add_temp("dex", joblv * 5);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, joblv :), joblv * 8);
        return 1;
}

void remove_effect(object me, int joblv)
{
        if ((int)me->query_temp("special2/xianyun/joblv"))
        {
		me->add_temp("apply/defense", -1 * joblv * 10);
		me->add_temp("dex", -1 * joblv * 5);
	        me->delete_temp("special2/xianyun");
	        tell_object(me, "������Ұ���˹���ϡ�\n");
        }
}

