
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"���յ�"NOR, ({ "yangyan dan","dan" }));
   set_weight(100);
   set("unit", "��");
   set("long","����һ���ɶ������������������ɵĵ�ҩ,����(fu dan)��������.\n");
   set("value", 150000);
   
}

void init()
{
	add_action("do_fu","fu");
}
int do_fu(string arg)
{
	object me,ob;int i;
	ob=this_object();me=this_player();
	if(!arg||(arg!="dan"&&arg!="��"))
		return notify_fail("��Ҫ����ʲô?\n");
                            if(me->query("per")>30)
		return notify_fail("�㶼��ô���ˣ�����ʲô�գ����ñ��˻��˰���\n");
	me->add("per",1);
	message_vision("$N������һ��[���յ�]���о����Լ������ˡ�\n",me);
	destruct(ob);
	return 1;
}