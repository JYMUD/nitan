#include <ansi.h>
inherit ITEM;
void create()
{
      	set_name(HIR"����ɢ"NOR, ({ "yuqing san","san"}));
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

        if( time()-query("eat_drug/yuqingsan", me)<2400 )
                return notify_fail("��շ��ù�ҩʱ�䲻�ã���ҩ�Է�����Ч���Ժ���ܼ������á�\n"); 
    
        addn("max_jingli", 10+random(5), me);message_vision(HIB"$N��������ɢ������ȥ,�о��Լ��ľ����������ӡ�\n"NOR,me);
      set("eat_drug/yuqingsan", time(), me);
     	destruct(this_object());
      	return 1;
}
