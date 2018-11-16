#include <ansi.h>
inherit ROOM;
void faya(object me);
void jiaoshui(object me);
void chucao(object me);
void zhuochong(object me);
void shouhuo(object me);


void create()
{
	set("short", "��԰");
	set("long", @LONG
�����ǡ�����ҽ�ɡ�����ţ�Ĺ�԰�������������˼��ù���������
��Ϊ��Ƣ���Ź֣��벻��ʲô��Ϊ�����������Ƭ��԰�Ե��൱�ư�
˥�䡣
LONG
	);
       set("outdoors", "mingjiao");

	set("exits", 
	([
          	"south" : __DIR__"hudiegu",
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

    	if (arg != "shu zhong")
       	return notify_fail("�������������ʺ���������ֲ��\n");
       
	if( query_temp("zhongshu", me) )
       	return notify_fail("���ϴ��ֵĹ�������������\n");

	ob = present("shu zhong", me);
	if (!ob)
		return notify_fail("��Ҫ��ʲô��\n");

	destruct(ob);

	message_vision (MAG"$N�ڵ�������һ��С�ӣ�С�ĵذѹ��������������档\n"NOR,me);

	me->start_busy(5);
set_temp("zhongshu", 1, 	me);

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
	message_vision (HIR"ֻ����ս����ƻ�$N���µĹ����ۿ��ž�һ���ɿ��ˡ�\n"NOR,me);

set_temp("need_jiaoshui", 1, 	me);
}

int do_jiaoshui()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_jiaoshui", me) )
		return notify_fail("��Ҫ��ʲô��\n");
	
	if (!ob = present("shui hu", me))
		return notify_fail("������û��ˮ������ʲô��ˮ��\n");

	message_vision (HIB"$N�ó�һ��ˮ������ϸ�ؽ����Լ��ֵĹ����ϡ�\n"NOR,me);
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
	message_vision (GRN"����ʱ������ƣ�$N���µĹ����Ա߽���������һЩ�Ӳݡ�\n"NOR,me);

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
	message_vision (HIY"�ֹ���һ�ᣬ$NͻȻ�����м�ֻ�������ڷ��ؿ��ɹ����ĸ�����\n"NOR,me);

set_temp("need_zhuochong", 1, 	me);
}

int do_zhuochong()
{
    	object me = this_player();

	if( !query_temp("need_zhuochong", me) )
		return notify_fail("��Ҫ��ʲô��\n");
	
	message_vision (HIB"$N����Σ�գ��������ϰѺ���һ��һ���ҳ���ɱ����\n"NOR,me);
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
	object guo1, guo2, guo3, guo4; 

	i = 1 + random(3);

	if (i == 1)
	{
		guo1 = new(__DIR__"/yao/guolei");
   		guo1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo1->name()+HIM"��\n"NOR, this_player());
	}
	else if (i == 2)
	{
		guo1 = new(__DIR__"/yao/guolei");
   		guo1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo1->name()+HIM"��\n"NOR, this_player());

		guo2 = new(__DIR__"/yao/guolei");
   		guo2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo2->name()+HIM"��\n"NOR, this_player());

	}
	else if (i == 3)
	{
		guo1 = new(__DIR__"/yao/guolei");
   		guo1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo1->name()+HIM"��\n"NOR, this_player());

		guo2 = new(__DIR__"/yao/guolei");
   		guo2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo2->name()+HIM"��\n"NOR, this_player());

		guo3 = new(__DIR__"/yao/guolei");
   		guo3->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo3->name()+HIM"��\n"NOR, this_player());

	}
	else
	{
		guo1 = new(__DIR__"/yao/guolei");
   		guo1->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo1->name()+HIM"��\n"NOR, this_player());

		guo2 = new(__DIR__"/yao/guolei");
   		guo2->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo2->name()+HIM"��\n"NOR, this_player());

		guo3 = new(__DIR__"/yao/guolei");
   		guo3->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo3->name()+HIM"��\n"NOR, this_player());

		guo4 = new(__DIR__"/yao/guolei");
   		guo4->move(me);
   		message_vision(HIM"$N�ջ���һ��"+guo4->name()+HIM"��\n"NOR, this_player());

	}

	me->start_busy(2);

	message_vision (HIR"���ڵ����ջ�ļ��ڣ�$N����ջ���"+chinese_number(i)+"�Ź�ʵ��\n"NOR,me);

addn("combat_exp", 1000+random(i*1000), 	me);
addn("potential", 300+random(i*300), 	me);
        delete_temp("zhongshu", me);


	tell_object(this_player(),MAG"������������Ͷ��������Ǳ�ܶ�����������\n"NOR);


}

int valid_leave(object me, string dir)
{
	if( query_temp("zhongshu", me) )
		 return notify_fail("�ȹ�ʵ���������Ҳ���١�\n");
	else return ::valid_leave(me, dir);
}

int discmds()
{
        tell_object(this_player(),"��Ȼ�����������ר�������ɣ�\n");
        return 1;
}
