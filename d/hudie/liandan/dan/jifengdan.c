#include <ansi.h>
inherit ITEM;
void create()
{
    	set_name(HIG"�������굤"NOR, ({ "jifengzhouyu dan","dan"}));
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

  	if (!me->is_fighting())
		return notify_fail("������û����ս���У�����Ҳûʲô�á�\n");

	me->start_busy(0);
  	message_vision(HIG"$N����һ�ż������굤�����缲�磬������æ��״̬��ת��һ���ֹ��˹�����\n"NOR,me);
      	destruct(this_object());
      	return 1;
}
