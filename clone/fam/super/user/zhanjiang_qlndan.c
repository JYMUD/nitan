#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "�����ڵ�" NOR, ({"qilinneidan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "��˵�����ڵ�������ǧ���������ڵ���ӵ���ޱߵ�������\n" + 
        	                "��ʳ(fushi qilinneidan ����id)�������������֪ʶ�༼��1����\n" HIC
        	                "ӵ���ߣ�zhanjiang\n" NOR);
                set("unit", "��");
                set("owner", "zhanjiang"); // ��ӵ����
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
	string skid;
	
	me = this_player();

	if (! arg )
		return notify_fail("��Ҫ��ʳʲô��\n");

	if (! sscanf(arg, "qilinneidan %s", skid))
		return notify_fail("ָ���ʽ��fuyong qilinneidan ����ID\n");

	arg = "qilinneidan";

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����������\n");

	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "�Ѿ���������Ұ󶨣�\n");

	if (! me->query_skill(skid, 1))
		return notify_fail("��û��������ܣ���ȷ�������Ƿ���ȷ��\n");
	
	if (skid == "zuoyou-hubo")
		return notify_fail("���һ�������������\n");

	if (("/kungfu/skill/" + skid)->type() == "knowledge")
		return notify_fail("֪ʶ�༼�ܲ���������\n");

	if (("/kungfu/skill/" + skid)->type() != "martial")
		return notify_fail("�����δ�������Ͳ���������\n");

	me->set_skill(skid, me->query_skill(skid, 1) + 1);

	tell_object(me, HIG "��ϲ�������" + ob->name() + HIG "��" + to_chinese(skid) + "����1����\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " ʹ��" + ob->name() + 
	                                                "�������ܣ�" + to_chinese(skid) + "��\n");

	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}