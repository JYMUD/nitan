#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "Ԫ�����е�" NOR, ({"yuanshenwuxingdan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIY "ʹ�ã�changewx ���У�Ԫ�����е����ָ������Ԫ����������һ�Ρ�\n" + HIC
        			"ӵ���ߣ�wuyinqiang\n" NOR);
                set("unit", "��");
                set("owner", "wuyinqiang"); // ��ӵ����
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "changewx");       
}

int do_use(string arg)
{
	object ob, me;
	string wuxing;
	
	mapping wx = ([
	   "��" : 0,
	   "ľ" : 1,
	   "ˮ" : 2,
	   "��" : 3,
	   "��" : 4,
	]);

	me = this_player();

	if (! arg )
		return notify_fail("ָ���ʽ��changewx [����]\n");

	if (arg != "��" && arg != "ľ" && arg != "ˮ" &&
	    arg != "��" && arg !="��")
	    	return notify_fail("����������󣬷�Χ����ľˮ������\n");

	wuxing = arg;
	
	arg = "yuanshenwuxingdan";

	if (me->query("yuanshen/wuxing") == wx[wuxing])
		return notify_fail("�������Ѿ���" + wuxing + "�����ˣ�\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����������\n");


	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "�Ѿ���������Ұ󶨣�\n");
	

	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "��Ԫ�����б��Ϊ��" HIC + wuxing + HIG "��\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " ʹ��" + ob->name() + 
	                                                "Ԫ�����б��Ϊ��" + wuxing + "��\n");

	me->set("yuanshen/wuxing", wx[wuxing]);
	me->set("yuanshen/last_change_wuxing", time());

	me->save();
	
	destruct(ob);
	
	return 1;
}

int query_autoload()
{
	return 1;
}