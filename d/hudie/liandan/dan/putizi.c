#include <ansi.h>
inherit ITEM;
void create()
{
      	set_name(YEL"������"NOR, ({ "puti zi","zi"}));
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
  	int maxneili,neili;
    	neili=query("neili", me);
    	maxneili=query("max_neili", me);
    
  	if(!id(arg)) return 0;
  	if(me->is_busy()) return notify_fail("����һ��������û����ɡ�\n");
        if( time()-query("eat_drug/putizi", me)<1800 )
                return notify_fail("�����������Ϣδ���������������ܸе������嵴������óȻ��ʳ��\n");

        addn("max_neili", 10+random(15), me);message_vision(HIG"$N���������ӳ�����ȥ,�о����ﴫ��һ��������,������Ϊ������������!!!!!\n"NOR,me);
      set("eat_drug/putizi", time(), me);
      	destruct(this_object());
      	return 1;
}
