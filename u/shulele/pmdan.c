
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"ƴ����"NOR, ({ "pinming dan","dan" }));
   set_weight(100);
   set("unit", "��");
   set("long","����һ���ɶ��ֲ�֪����Ʒ���ɵĵ�ҩ,����(fu dan)����֪���ᷢ��ʲô.\n");
   set("value", 50000);
   
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
	message_vision("$N������һ��[ƴ����].\n",me);
if(random(10)>6)
{
message_vision("$N�о��������ƺ�������.\n",me);
me->add("max_force",15+random(30));
}
else
me->set("gin",-1);
	destruct(ob);
	return 1;
}