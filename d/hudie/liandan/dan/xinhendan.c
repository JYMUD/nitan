#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIG"�ĺ�������"NOR, ({ "xinhen dan","dan"}));
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
  	object me = this_player();
    
  	if(!id(arg)) return 0;
  	if(me->is_busy()) return notify_fail("����һ��������û����ɡ�\n");
    
addn("shen", -50000, 	me);
 	message_vision(HIB"$N�����ĺ�������������ȥ���о����ﴫ��һ�����⣬˫��ð������ɱ��������\n"NOR,me);
       destruct(this_object());
       return 1;
}
