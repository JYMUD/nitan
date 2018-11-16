#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void finish(object me, object ob);

void create()
{
        set_name(RED"����"NOR, ({ "lian dao"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ�Ѳ�ҩ�˳��õ�����������Ѱ�ң�search������ҩ�ġ�\n");
                set("unit", "��"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_blade(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_search", "search");
}

int do_search()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "liandao" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "liandao" )
        	return notify_fail("�㲻���Ź��ߣ��ҵ�ҩ��Ҳ���������\n");

        if( strsrch(query("short", environment(me)),"��")<0
         && strsrch(query("short", environment(me)),"��")<0
              && strsrch(query("long", environment(me)),"��")<0
              && strsrch(query("long", environment(me)),"��")<0 )


  	return notify_fail("ֻ�вݴ��в��п����ҵ�ҩ��!\n");
  	
	if(me->is_busy())
  	return notify_fail("��������æ,��һ�����Ұ�!\n");

  	if( query("search", environment(me))>time() )
  	return notify_fail("Ϊ�˻����������벻Ҫ��̤��ƺ!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N�Ĵ������������ܲ����ҵ����õ�ҩ�ݡ�\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object cao;

  	if(random(5)>3) 
	{
  		me->start_busy(2);
  		message_vision( HIW"Ѱ��һ��֮��$Nһ������ֻ��ʧ����̾�˿�����\n"NOR, this_player());

   	}
  
  	else if ( random(20)<1) 
	{
  		message_vision( HIG"$N�ò������ҵ�һ�����õ�ҩ�ݣ���������ȴ��������������!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("search", time()+20, 		environment(me));

		cao=new(__DIR__"/yao/caolei");
   		cao->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$NͻȻ����һ��"+cao->name()+HIR"����æ����������С������ؽ����ȡ������\n"NOR, this_player());
	}
}

