#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIW"�Ż���¶��"NOR, ({ "jiuhuayulu wan","wan"}));
     	set_weight(100);
     	if( clonep() )
            	set_default_object(__FILE__);
     	else 
	{
             	set("long", "�Ż���¶�����һ�����ҩʦ������ʥҩ��ֻҪ����һ�����ڣ����ܰ����Ȼ�����\n");
             	set("unit", "��"); 
            	set("no_get",1);
            	set("no_give",1);   
             	set("value",100000);

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
  	
	if(!id(arg)) 
		return 0;
    
addn("combat_exp", random(5000), 	me);
 
//����
     set("jingli",query("max_jingli",  me), 	me);
//����
      set("eff_jing",query("max_jing",  me), 	me);
     set("jing",query("max_jing",  me), 	me);
//����
     set("neili",query("max_neili",  me), 	me);
//��Ѫ
     set("eff_qi",query("max_qi",  me), 	me);
     set("qi",query("max_qi",  me), 	me);
    
  	message_vision(HIR"$N����һ�žŻ���¶�裬��������˲��Ȭ��������Ҳ��������ࡣ\n"NOR,me);
     	destruct(this_object());
     	return 1;
}
