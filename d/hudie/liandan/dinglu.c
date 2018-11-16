#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(HIY"��ͨ��¯"NOR, ({ "putong dinglu", "dinglu" }));
	set_weight(500);
	set_max_encumbrance(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ��ССԲԲ����ͨ��¯��ҩ��������������ҩ������\n");
		set("value", 1000000);
             	set("no_get",1);
            	set("no_give",1);
	}
}

int is_container() { return 1; }

void init()
{
    	if (environment()==this_player())
        	add_action("do_liandan", "liandan");
}


int do_liandan()
{  	
	object me = this_player();
	object ob = this_object();
	object *yao;
	int yaoxing, i, lv;

	if( !query("peifang", me) || !query("mubiao", me) )
        	return notify_fail("�㻹û�õ��䷽�أ���������ʲô������\n");

	yao = all_inventory(ob);
	lv = sizeof(yao);
	if (lv==0)
        	return notify_fail("�Ȱ�ҩ�ķŵ���¯���������ɡ�\n");

	if (me->is_busy())
        	return notify_fail("��������æ���ء�\n");

	if( query_temp("fire", me) )
        	return notify_fail("�Ȱ��ϴεĵ��������ڸɱ�İɡ�\n");

    	for(i=0; i<lv; i++) 
	{
        	if( !query("yaoxing", yao[i]) )
        		return notify_fail("��ôʲô���߰���Ķ�������¯����ţ�\n");

		yaoxing+=query("yaoxing", yao[i]);
		destruct(yao[i]);
       }

   	message_vision(MAG"$N���պ���ţ�����䷽����ҩ�ķŽ���¯��ר����־�����ơ�\n"NOR, this_player());

	me->start_busy(8);
set_temp("fire", 1, 	me);
set_temp("yaoxing", yaoxing, 	me);
set_temp("lv", lv, 	me);

	call_out("fire",8, me);
	return 1;
}

void fire(object me)
{
	int fire;

	if( query("neili", me)<40000 )
	{
		message_vision (HIY"����һ�ᣬ¯�е��¶��ƺ���Щ�½���$N��״��æ���˼�����̡�\n"NOR,me);
	}
	else if( query("neili", me)<200000 )
	{
		message_vision (HIY"����һ�ᣬ¯�е��¶��ƺ���Щ�½���$N��״��æ�߶�������¯���¶�����������\n"NOR,me);
addn("neili", -10000, 		me);
addn_temp("fire", 1, 		me);
	}
	else
	{
		message_vision (HIY"����һ�ᣬ¯�е��¶��ƺ���Щ�½���$N��״��æ�߶��������Ķ�"+HIR+"��ζ���"+HIY+"��¯�л���һ������������\n"NOR,me);
addn("neili", -50000, 		me);
addn_temp("fire", 2, 		me);
	}
    	me->improve_skill("liandan-shu", me->query_int()*100+random(1000));
    addn("combat_exp", 500+random(500), 	me);
    addn("potential", 100+random(200), 	me);
	tell_object(me,WHT"����������ľ���Ǳ��������������������Ҳ����ߡ�\n"NOR);

	me->start_busy(5);
    	switch ( random(2) ) 
    	{

    		case 0:
     			call_out("fire",8, me);
		break;

    		case 1:
     			call_out("shoudan",8, me);
		break;

    	}

}

void shoudan(object me)
{

	object dan;

	if( query_temp("yaoxing", me) != query("peifang", me) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"�����䷽���ԣ�$N������һ������ҩƷ��\n"NOR, this_player());
	}

	else if( random(query_temp("fire", me))<random(query_temp("lv", me)) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"�����䷽��ȷ������������Ʒ���ѣ�$N������һ������ҩƷ��\n"NOR, this_player());
 	}
	else
	{
		dan=new(__DIR__"/dan/"+query("mubiao", me));
		dan->move(me);
   		message_vision(HIR"����ǧ����࣬$N��������һ������"+query("name", dan)+HIR"��\n"NOR,this_player());
   		message_vision(HIB"$N��æ�����������ĵ�ҩ���ڻ��\n"NOR, this_player());

 	}
delete_temp("yaoxing", 	me);
delete_temp("fire", 	me);
delete_temp("lv", 	me);

delete("peifang", 	me);
delete("mubiao", 	me);
}