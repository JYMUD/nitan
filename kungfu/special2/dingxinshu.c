
// ������ Create by Rcwiz for yhonline 04/21 2010

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "������" NOR; }

int perform(object me, string skill)
{
	// 2ת��ʹ�ÿ��������180�����һ���
	// �����ǰ�ȼ�����180����ʾ˵��
	if (me->query("thborn/ok") && me->query_skill("zuoyou-hubo",1) < 180)
	{
		me->set_skill("zuoyou-hubo", 180);
		me->save();
                return notify_fail("���������һ���180����\n");
	}
        else
        {
      		return notify_fail("���������㶨����,��ʩչ���һ�������ǣ�ơ�\n"
          	   		   "ʹ�ú�ɻ�����һ���180��,ͬʱ������\n"
          	   		   "�о���380��.�����ȥ�����ܴﵽ���ټ�\n"
                                   "���о����һ�����400����\n");
       }
}