#include <ansi.h>
#include <weapon.h>
inherit AXE;

void finish(object me, object ob);

void create()
{
        set_name(MAG"С��ͷ"NOR, ({ "fu tou"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ�Ѳ�ҩ�˳��õ�С��ͷ������������kanfa��ľ��ҩ�ġ�\n");
                set("unit", "��"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_axe(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_kanfa", "kanfa");
}

int do_kanfa()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "futou" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "futou" )
        	return notify_fail("�㲻���Ź��ߣ��ҵ�ҩ��Ҳ������������\n");

  	//if( !query("outdoors", environment(me)) )
  	//return notify_fail("���ڷ������ܿ���ʲô��������\n");

    if( strsrch(query("short", environment(me)),"��")<0
     && strsrch(query("short", environment(me)),"ľ")<0
         && strsrch(query("short", environment(me)),"��")<0
              && strsrch(query("long", environment(me)),"��")<0
              && strsrch(query("long", environment(me)),"ľ")<0
              && strsrch(query("long", environment(me)),"��")<0 )


  	return notify_fail("ֻ����������п����ҵ�ҩ����ľ!\n");
  	
	if(me->is_busy())
  	return notify_fail("��������æ,��һ���ٿ���!\n");

  	if( query("kanfa", environment(me))>time() )
  	return notify_fail("Ϊ�˻����������벻Ҫ�ķ���ľ!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N�Ĵ������������ܲ����ҵ����õ���ľ��\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object mu;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"Ѱ��һ��֮��$Nһ������ֻ��ʧ����̾�˿�����\n"NOR, this_player());

   	}
  
  	else if ( random(20)<2) 
	{
  		message_vision( HIG"$N�ò������ҵ�һ�����õ���ľ����������ȴ���ָ�ͷ������!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("kanfa", time()+20, 		environment(me));

		mu=new(__DIR__"/yao/mulei");
   		mu->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$NͻȻ����һ��"+mu->name()+HIR"������æȡ����ͷ���Ѿ�ȫ���������俳��������\n"NOR, this_player());
	}
}
