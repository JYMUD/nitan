#include <ansi.h>
inherit ROOM;
void faya(object me);
void jiaoshui(object me);
void chucao(object me);
void zhuochong(object me);
void shouhuo(object me);


void create()
{
	set("short", "花圃");
	set("long", @LONG
這裡是『蝶谷醫仙』胡青牛的葯圃，零零落落種了幾株植物。胡大
夫為人脾氣古怪，請不到什麼人為他打理，因此這塊葯圃顯得相當破敗
衰落。
LONG
	);
       set("outdoors", "mingjiao");

	set("exits", 
	([
          	"north" : __DIR__"hudiegu",
	]));
        set("objects", 
	([
	]));
    
	setup();
}

void init ()
{
  	add_action("do_mai","mai");
  	add_action("do_jiaoshui","jiaoshui");
  	add_action("do_chucao","chucao");
  	add_action("do_zhuochong","zhuochong");
    	add_action("discmds",({"sleep","respitate","exert","array","duanlian",
	"ansuan","touxi","persuade","teach","exert","exercise","study","learn",
	"kill","steal","conjure","fight","hit","perform","prcatice","scribe","surrender"}));

}

int do_mai(string arg)
{
    	object ob;
    	object me = this_player();

	if (me->is_busy())
  		return notify_fail("你現在正忙,等一下再種吧!\n");

	if (!arg)
		return notify_fail("你要種什麼？\n");

    	if (arg != "hua zhong")
       	return notify_fail("這樣東西並不適合在這裡種植。\n");
       
	if( query_temp("zhonghua", me) )
       	return notify_fail("你上次種的花花草草都長好了嗎？\n");

	ob = present("hua zhong", me);
	if (!ob)
		return notify_fail("你要種什麼？\n");

	destruct(ob);

	message_vision (MAG"$N在地上挖了一個小坑，小心地把鮮花種籽埋在裡面。\n"NOR,me);

	me->start_busy(5);
set_temp("zhonghua", 1, 	me);

       call_out("faya",8, me);
	return 1;

}


void faya(object me)
{
	message_vision (HIG"$N耐心地等了一段時間，只見一根綠油油的嫩苗破土而出！\n"NOR,me);

	me->start_busy(5);

    	switch (random(4)) 
    	{
    		case 0: 
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("chucao",8, me);
		break;

    		case 2:
     			call_out("zhuochong",8, me);
		break;

    		case 3:
     			call_out("shouhuo",8, me);
		break;

    	}
}

void jiaoshui(object me)
{
	message_vision (HIR"只見天空驕陽似火，$N種下的植物眼看着就一點點乾枯了。\n"NOR,me);

set_temp("need_jiaoshui", 1, 	me);
}

int do_jiaoshui()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_jiaoshui", me) )
		return notify_fail("你要做什麼？\n");
	
	if (!ob = present("shui hu", me))
		return notify_fail("你身上沒有水壺，拿什麼澆花？\n");

	message_vision (HIB"$N拿出一把水壺，仔細地澆在自己種的植物上。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_jiaoshui", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("chucao",8, me);
		break;

    		case 1:
     			call_out("zhuochong",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}

void chucao(object me)
{
	message_vision (GRN"隨着時間的推移，$N種下的植物旁邊漸漸長出了一些雜草。\n"NOR,me);

set_temp("need_chucao", 1, 	me);
}

int do_chucao()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_chucao", me) )
		return notify_fail("你要做什麼？\n");
	
	if (!ob = present("yao chu", me))
		return notify_fail("你身上沒有葯鋤，拿什麼除草？\n");

	message_vision (HIB"$N拿出葯鋤，仔細地把周圍的雜草清除乾淨。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_chucao", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("zhuochong",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}

void zhuochong(object me)
{
	message_vision (HIY"又過了一會，$N突然發現有幾隻害蟲正在瘋狂地啃噬植物的根莖！\n"NOR,me);

set_temp("need_zhuochong", 1, 	me);
}

int do_zhuochong()
{
    	object me = this_player();

	if( !query_temp("need_zhuochong", me) )
		return notify_fail("你要做什麼？\n");
	
	message_vision (HIB"$N不顧地面骯髒，趴在地上把害蟲一條一條找出來殺死。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_zhuochong", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("chucao",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}
void shouhuo(object me)
{
	int i;
	object hua1, hua2, hua3, hua4; 

	i = 1 + random(4);

	if (i == 1)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua1->name()+HIM"！\n"NOR, this_player());
	}
	else if (i == 2)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

	}
	else if (i == 3)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua3->name()+HIM"！\n"NOR, this_player());

	}
	else
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua3->name()+HIM"！\n"NOR, this_player());

		hua4 = new(__DIR__"/yao/hualei");
   		hua4->move(me);
   		message_vision(HIM"$N收穫了一朵"+hua4->name()+HIM"！\n"NOR, this_player());

	}

	me->start_busy(2);

	message_vision (HIR"終於到了收穫的季節！$N這次收穫了"+chinese_number(i)+"朵花！\n"NOR,me);

addn("combat_exp", 1000+random(i*1000), 	me);
addn("potential", 300+random(i*300), 	me);

        delete_temp("zhonghua", me);


	tell_object(this_player(),MAG"由於你的辛勤勞動，經驗和潛能都有所增長。\n"NOR);


}

int valid_leave(object me, string dir)
{
	if( query_temp("zhonghua", me) )
		 return notify_fail("等花種出來再走也不遲。\n");
	else return ::valid_leave(me, dir);
}

int discmds()
{
        tell_object(this_player(),"既然到了這裡，還是專心種花吧！\n");
        return 1;
}
