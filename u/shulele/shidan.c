
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"ʬ��"NOR, ({ "shi dan","dan" }));
   set_weight(100);
   set("unit", "��");
   set("long","����һ����ʬ�����ɵĵ�ҩ,����(fu dan)�󣬻ᷢ��ʲô������?\n");
   set("value", 0);
   set("no_give",1);
   set("no_save",1);
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
	message_vision("$N������һ��[ʬ��].\n",me);
if(random(10)>8)
{
message_vision("$N�о���������ˬ�������ƺ������ˡ�\n",me);
me->add("max_force",10);
}else{
me->set("gin",-1);
	destruct(ob);
	return 1;
}
}