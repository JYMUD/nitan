
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "������˭" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
		object *t;
		object tob;
		int qi, jing;

		joblv = me->query_joblv();

		t = me->query_team(); // ����Ҫ��Ӳ���ʩչ

        if (time() - me->query_temp("special2/shewo/lasttime") < 60)
                return notify_fail("�ü�����һ������ֻ��ʩչһ�Ρ�\n");

		if (me->query("yhjob/job") != "����")
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

        message_vision(HIC "$N" HIC "˫Ŀ΢�գ���ʱȫ�����±�һ��������֣������أ������ɢ���� ��������\n" NOR, me);

		foreach (tob in t)
		{
			if (! objectp(tob))continue;

			if (1)
			{			
				tell_object(tob, HIW + me->name() + "ʩչ�����С�������˭�����ָ����ж��ѵľ�������Ѫ��\n" NOR);
				qi = 500 + me->query_joblv() * 50 + me->query("lhpoint/special/shewo")* 400;
				jing = 200 + me->query_joblv() * 30 + me->query("lhpoint/special/shewo") * 300;

				// �ָ�����״̬
				if (tob->query("eff_qi") + qi / 2 > tob->query("max_qi"))
						tob->set("eff_qi",tob->query("max_qi"));
				else
						tob->add("eff_qi", qi / 2);

				// �ָ���Ѫ
				if (tob->query("qi") + qi > tob->query("eff_qi"))
						tob->set("eff_qi", tob->query("eff_qi"));
				else
						tob->add("qi", qi);
				
				// �ָ�����/��������״̬
				if (tob->query("eff_jing") + jing / 2 > tob->query("max_jing"))
						tob->set("eff_jing", tob->query("max_jing"));
				else
						tob->add("eff_jing", jing / 2);

				if (tob->query("eff_jingli") + jing / 4 > tob->query("max_jingli"))
						tob->set("eff_jingli", tob->query("max_jingli"));
				else
						tob->add("eff_jingli", jing / 4);

				if (tob->query("jing") + jing / 2 > tob->query("eff_jing"))
						tob->set("jing", tob->query("eff_jing"));
				else
						tob->add("jing", jing / 2);

				if (tob->query("jingli") + jing / 2 > tob->query("eff_jingli"))
						tob->set("jingli", tob->query("eff_jingli"));
				else
						tob->add("jingli", jing / 2);
			}
		}
 
		me->set_temp("special2/shewo/lasttime", time());
        me->add("neili", -1000);
        me->start_busy(1);

        return 1;
}
