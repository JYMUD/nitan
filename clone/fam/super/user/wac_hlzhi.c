#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "����֥" NOR, ({"huolingzhi"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "����֥�������½�����ȵĵ�����������˴��֮����\n" + 
        	                "��ʳ(fushi huolingzhi)�������������������10�㡣\n" HIC
        	                "ӵ���ߣ�wac\n" NOR);
                set("unit", "��");
                set("owner", "wac"); // ��ӵ����
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "fushi");       
}

int do_use(string arg)
{
	object ob, me;
	
	me = this_player();

	if (! arg || arg != query("id"))
		return notify_fail("��Ҫ��ʳʲô��\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����������\n");

	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "�Ѿ���������Ұ󶨣�\n");
	
	me->add("drug_addneili", 10);

	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "��������������10�㣡\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " ʹ��" + ob->name() + "��\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}