
#include <ansi.h>

//inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "Ц̸����" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
	object *t;
	object tob;
	int dex, dodge;

	joblv = me->query_joblv();

	t = me->query_team(); // ����Ҫ��Ӳ���ʩչ

        if (me->query_temp("special2/tianxia"))
                return notify_fail("��Ц̸���¡��Ĺ�Ч��δ��ʧ���޷�ʩչ��\n");

	if (me->query("yhjob/job") != "��ʿ")
		return notify_fail("���ְҵ�����޷�ʩչ��\n");
		
	if (me->query("neili") < 1000)
		return notify_fail("����������㣬�޷�ʩչ��\n");

	if (joblv < 30)
		return notify_fail("���ְҵ�ȼ����㣬�޷�ʩչ��\n");		

	if (! arrayp(t))
		return notify_fail("�ü���ֻ������ӵ�ʱ��ʩչ��\n");
	t -= ({ 0 });
	if (sizeof(t) <= 1)
		return notify_fail("�ü���ֻ���ڶ�����ӵ�ʱ��ʩչ��\n");
			
        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIR "$N" HIR "���΢Ц����Ȼ�ֱ�һ�ӣ������� ����������\n" NOR, me);

	foreach (tob in t)
	{
		if (1)
		{			
			tell_object(tob, HIW + me->name() + "ʩչ�����С�Ц̸���¡���������ж��ѵĻرܼ���"
			                 "Ч�Ṧ�ȼ���\n" NOR);
			dex = 10 + me->query_joblv() * 4 + me->query("lhpoint/special/tianxia") * 20;
			dodge = 20 + me->query_joblv() + me->query("lhpoint/special/tianxia") * 10;

               		// �����ظ�ʩչ
			if (! tob->query_temp("special2/tianxia"))
			{
				tob->set_temp("special2/tianxia", 1);
				tob->add_temp("dex", dex);
				tob->add_temp("apply/dodge", dodge);
				tob->start_call_out( (: call_other, __FILE__, "remove_effect", tob, dex, dodge :), 
				                   60 + joblv * 10);
			}
		}
	}
 
        me->add("neili", -1000);
        me->start_busy(1);

        return 1;
}

void remove_effect(object me, int dex, int dodge)
{
	if (! objectp(me))return;
	
        if ((int)me->query_temp("special2/tianxia"))
        {
		me->add_temp("dex", -1 * dex);
		me->add_temp("apply/dodge", -1 * dodge);
	        me->delete_temp("special2/tianxia");
	        tell_object(me, "��Ц̸���¡��Ĺ�Ч�Ѿ���ʧ��\n");
        }
}

