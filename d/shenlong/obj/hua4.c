// hua4.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIC "�����" NOR, ({"feicui lan", "feicui", "lan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "��");
		set("long", "����һ��ǧ���ѵ�һ�������������˵�ܽ�ٶ���\n");
        	set("value", 1000000);
		set("only_do_effect", 1);
	}
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/feicui", me)<300 ) 
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n"); 
                return 1; 
        }

        set_temp("last_eat/feicui", time(), me); 
set_temp("nopoison", 3, 	me);
set("eff_jing",query("max_jing",  me), 	me);
set("jing",query("max_jing",  me), 	me);
set("eff_qi",query("max_qi",  me), 	me);
set("qi",query("max_qi",  me), 	me);
        message_vision("$N��" + name() + "�ӽ�������¾�������ȥ��\n", me);
	tell_object(me, HIG "\n��ֻ��һ�����������ķΣ���ʱ��̨һƬ"
		        "������������ˬ��\n" NOR);
	destruct(this_object());
	return 1;
}
