// tong.c ͨ������
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "ͨ������" NOR; }

int perform(object me, string skill, string arg)
{
        int i;
      
        object ob;

        if (me->query("neili") < 500)return notify_fail("���������㣬ͨ�����ۣ�\n");

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");
	        
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ���������ĸ�ʽ�д���\n"
                                   "��ʽ �� special tong <����id> \n");

	if (ob->query_temp("apply/invisible"))
                return notify_fail("����û������ˣ���������ĸ�ʽ�д���\n"
                                   "��ʽ �� special tong <����id> \n");		

	if (ob->query("special_skill/emperor"))
		return notify_fail("�������������ӣ����޷��鿴�����������\n");
		
	if (ob->query("special_skill/lonely"))
		return notify_fail("��������ɷ���ǣ����޷��鿴�����������\n");
				
	if (ob->query("yanjiu_test"))
                return notify_fail("��������ɷ���ǣ����޷��鿴�����������\n");	
                                   		
        write(HIW "��ʩչ��ͨ������֮�� ����\n" NOR, me);
	
        me->add("neili", -500);
        me->start_busy(2);

        "/cmds/usr/hp"->main(me, arg, 1);
        "/cmds/skill/cha"->main(me, arg, 1);

        return 1;
}
