
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"����ͷ"NOR, ({ "head"}));
   set_weight(100);
   set("unit", "��");
   set("long","����һ������ͷ,������(eat head)���ú�а��.\n");
   set("value", 50000);
   
}

void init()
{
	add_action("do_fu","eat");
}
int do_fu(string arg)
{
	object me,ob;int i;
	ob=this_object();me=this_player();
	if(!arg||(arg!="head"&&arg!="ͷ"))
		return notify_fail("��Ҫ��ʲô?\n");
	me->add("bellicosity",100);
	message_vision("$Nץ��һ��[����ͷ]���������������͸¶��а����\n",me);
	destruct(ob);
	return 1;
}