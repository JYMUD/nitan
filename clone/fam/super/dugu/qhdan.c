#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "ǧ�ص�" NOR, ({"qianhuidan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "��˵��ũ��������ǧ�Σ��ճɴ˵���\n" + 
        	                "��ʳ(fushi qianhuidan)��30�����ڿɶ��������о�����50�Ρ�\n" HIR
        	                /*"ӵ���ߣ�ӵ����ID*/"\n" NOR);
                set("unit", "��");
                set("owner", "ӵ����ID"); // ��ӵ����
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

/*
void init()
{
        add_action("do_use", "fushi");       
}
*/

int do_use(string arg)
{
	object ob, me;
	
	me = this_player();

	if (! arg || arg != query("id"))
		return notify_fail("��Ҫ��ʳʲô��\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����������\n");
/*
	if( query("owner", ob) != query("id", me) )
		return notify_fail(ob->name() + NOR "�Ѿ���������Ұ󶨣�\n");
*/

	if( !query("add_yanjiu_times50", me) || 
	query("add_yanjiu_times50", me)-time() <= 0 )
set("add_yanjiu_times50", time()+1800, 		me);
	else
	{
addn("add_yanjiu_times50", 1800, 		me);
	}


	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "��30�������о������������50�Σ�\n");
	tell_object(me,HIG"Ŀǰ��Ч����ʣ��ʱ�䣺"+sprintf("%d",query("add_yanjiu_times50", me))+"�롣\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
