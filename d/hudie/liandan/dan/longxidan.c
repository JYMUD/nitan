#include <ansi.h>
inherit ITEM;
#include <ansi.h>
void create()
{
     	set_name(HIY"��Ϭ�ٲݵ�"NOR, ({ "longxi dan","dan"}));
      	set_weight(100);
      	if( clonep() )
            	set_default_object(__FILE__);
       else 
	{       
         	set("unit", "��"); 
             	set("no_get",1);
            	set("no_give",1);
      	}
    	setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_eat", "eat");
}


int do_eat(string arg)
{
    	if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
	this_player()->clear_condition();
 
   	message_vision(HIC "$N������Ϭ�ٲݵ���һ�������ӵ������𣬽���������ȫ��Ѫ�������ص���������ʧ�ˡ�\n" NOR,this_player() );
    	destruct(this_object());
    	return 1;
}
