#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void finish(object me, object ob);

void create()
{
        set_name(HIC"ҩ��"NOR, ({ "yao chu"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��ҩ���������ڵ����ھ�wajue������ҩ�ġ�\n");
                set("unit", "��"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_hammer(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_wajue", "wajue");
}

int do_wajue()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "yaochu" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "yaochu" )
        	return notify_fail("�����е����Ź��߲�����ҩ��\n");

  	if( !query("outdoors", environment(me)) )
  	return notify_fail("���ڷ������ڸ�ʲô����Ҫ��ȥ�����ڣ�\n");

  	if(!sscanf(base_name(environment(me)),"/d/wudang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/quanzhen/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/hengshan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/taishan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/huashan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/tiezhang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/gaochang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/kunlun/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/songshan/%*s"))
  	return notify_fail("ֻ����ɽ�󴨣��羰����֮���ſ����ھ�ҩ��!\n");
  	
	if(me->is_busy())
  	return notify_fail("��������æ,��һ�����ڰ�!\n");

  	if( query("wajue", environment(me))>time() )
  	return notify_fail("����ոձ����ھ�������һ��������!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N����ҩ�����ڵ���һ�������٣�\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object gen;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"$N�е������ڵ�ʲô������,��ϸһ��ԭ����ʯ��!\n"NOR, this_player());

   	}
  
   else if ( random(20)<2) 
	{
  		message_vision( HIG"$NͻȻ����������һ����,��ͷ�ڶ���!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("wajue", time()+120, 		environment(me));

		gen=new(__DIR__"/yao/genlei");
   		gen->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N����ҩ���ٵ����ߣ��ڳ���һ��"+gen->name()+HIR"��\n"NOR, this_player());
	}
}