#include <ansi.h>
inherit ROOM;
void faya(object me);
void jiaoshui(object me);
void chucao(object me);
void zhuochong(object me);
void shouhuo(object me);


void create()
{
	set("short", "����");
	set("long", @LONG
�����ǡ�����ҽ�ɡ�����ţ��ҩ�ԣ������������˼���ֲ�����
��Ϊ��Ƣ���Ź֣��벻��ʲô��Ϊ������������ҩ���Ե��൱�ư�
˥�䡣
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
  		return notify_fail("��������æ,��һ�����ְ�!\n");

	if (!arg)
		return notify_fail("��Ҫ��ʲô��\n");

    	if (arg != "hua zhong")
       	return notify_fail("�������������ʺ���������ֲ��\n");
       
	if( query_temp("zhonghua", me) )
       	return notify_fail("���ϴ��ֵĻ����ݲݶ���������\n");

	ob = present("hua zhong", me);
	if (!ob)
		return notify_fail("��Ҫ��ʲô��\n");

	destruct(ob);

	message_vision (MAG"$N�ڵ�������һ��С�ӣ�С�ĵذ��ʻ������������档\n"NOR,me);

	me->start_busy(5);
set_temp("zhonghua", 1, 	me);

       call_out("faya",8, me);
	return 1;

}


void faya(object me)
{
	message_vision (HIG"$N���ĵص���һ��ʱ�䣬ֻ��һ�������͵���������������\n"NOR,me);

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
	message_vision (HIR"ֻ����ս����ƻ�$N���µ�ֲ���ۿ��ž�һ���ɿ��ˡ�\n"NOR,me);

set_temp("need_jiaoshui", 1, 	me);
}

int do_jiaoshui()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_jiaoshui", me) )
		return notify_fail("��Ҫ��ʲô��\n");
	
	if (!ob = present("shui hu", me))
		return notify_fail("������û��ˮ������ʲô������\n");

	message_vision (HIB"$N�ó�һ��ˮ������ϸ�ؽ����Լ��ֵ�ֲ���ϡ�\n"NOR,me);
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
	message_vision (GRN"����ʱ������ƣ�$N���µ�ֲ���Ա߽���������һЩ�Ӳݡ�\n"NOR,me);

set_temp("need_chucao", 1, 	me);
}

int do_chucao()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_chucao", me) )
		return notify_fail("��Ҫ��ʲô��\n");
	
	if (!ob = present("yao chu", me))
		return notify_fail("������û��ҩ������ʲô���ݣ�\n");

	message_vision (HIB"$N�ó�ҩ������ϸ�ذ���Χ���Ӳ�����ɾ���\n"NOR,me);
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
	message_vision (HIY"�ֹ���һ�ᣬ$NͻȻ�����м�ֻ�������ڷ��ؿ���ֲ��ĸ�����\n"NOR,me);

set_temp("need_zhuochong", 1, 	me);
}

int do_zhuochong()
{
    	object me = this_player();

	if( !query_temp("need_zhuochong", me) )
		return notify_fail("��Ҫ��ʲô��\n");
	
	message_vision (HIB"$N���˵��氹�࣬ſ�ڵ��ϰѺ���һ��һ���ҳ���ɱ����\n"NOR,me);
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
   		message_vision(HIM"$N�ջ���һ��"+hua1->name()+HIM"��\n"NOR, this_player());
	}
	else if (i == 2)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua1->name()+HIM"��\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua2->name()+HIM"��\n"NOR, this_player());

	}
	else if (i == 3)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua1->name()+HIM"��\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua2->name()+HIM"��\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua3->name()+HIM"��\n"NOR, this_player());

	}
	else
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua1->name()+HIM"��\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua2->name()+HIM"��\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua3->name()+HIM"��\n"NOR, this_player());

		hua4 = new(__DIR__"/yao/hualei");
   		hua4->move(me);
   		message_vision(HIM"$N�ջ���һ��"+hua4->name()+HIM"��\n"NOR, this_player());

	}

	me->start_busy(2);

	message_vision (HIR"���ڵ����ջ�ļ��ڣ�$N����ջ���"+chinese_number(i)+"�仨��\n"NOR,me);

addn("combat_exp", 1000+random(i*1000), 	me);
addn("potential", 300+random(i*300), 	me);

        delete_temp("zhonghua", me);


	tell_object(this_player(),MAG"������������Ͷ��������Ǳ�ܶ�����������\n"NOR);


}

int valid_leave(object me, string dir)
{
	if( query_temp("zhonghua", me) )
		 return notify_fail("�Ȼ��ֳ�������Ҳ���١�\n");
	else return ::valid_leave(me, dir);
}

int discmds()
{
        tell_object(this_player(),"��Ȼ�����������ר���ֻ��ɣ�\n");
        return 1;
}
