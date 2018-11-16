#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "�����ɲ�" NOR, ({"bingjixiancao"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIG "�����ɲ��˳�������ɽ����ǧ�귽�ɳ��Σ���ɫ��ͬ���弡���ҽ����ѩ������͸�ǣ�\n" + 
        	                "��ʳ(fushi bingjixiancao)����������������ڹ�1����\n" HIC
        	                "ӵ���ߣ�xuantian\n" NOR);
                set("unit", "��");
                set("owner", "xuantian"); // ��ӵ����
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
	
	me->set_skill("force", me->query_skill("force", 1) + 1);
	
	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "�󣬻����ڹ�����1����\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " ʹ��" + ob->name() + "��\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}