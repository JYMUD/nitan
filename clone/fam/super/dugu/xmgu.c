#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "ѪĢ��" NOR, ({"xuemogu"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "ѪĢ����������99������֮Ѫ���ɡ�\n" + 
        	                "��ʳ(fushi xuemogu)�������������������5�㡣\n" HIC
        	                /*"ӵ���ߣ�ӵ����ID*/"\n" NOR);
                set("unit", "��");
                set("owner", "ӵ����ID"); // ��ӵ����
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
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
/*
	if( query("owner", ob) != query("id", me) )
		return notify_fail(ob->name() + NOR "�Ѿ���������Ұ󶨣�\n");
*/	
   addn("drug/jingli", 10, me);

	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "��������������5�㣡\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
