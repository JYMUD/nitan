#include <ansi.h>
#define GIFT_NAME "����"
// ���ε����﷢��
#define THIS_GIFT_USER "2013_����"
// �ϴε����﷢��
#define LAST_GIFT_USER "2013_��������5"

inherit ITEM;

void create()
{
	set_name(HIR + GIFT_NAME + NOR, ({"zong zi","zong", "zi"}));
	set_weight(200);
	set("unit", "��");
	set("long",HIG"NT��ʦ�ص�Ϊ��������Ķ������ӣ�����������ζ�����ӣ�\nƷ��(eat)һ����ʲôζ����\n"NOR);
	set("value", 0);
	set("no_give",1);
	set("no_get",1);
	set("no_put",1);
	set("no_drop",1);
        setup();
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me;
	me = this_player();
	
	if (!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
	
	if (query(THIS_GIFT_USER, me) && query("gift_dw", me) == (CHINESE_D->chinese_time(7, ctime(time()))) )  
	{
		tell_object(me,HIY "�����ʹ��ͻȻ��һ�������г��֣�һ��ץ�������е����ӣ���������Ѿ��Թ��˰ɣ��ɱ�̰��Ŷ����˵�꽫���������ˡ�\n"NOR);
		destruct(this_object());	
		return 1;
	}
	
	if ( (CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/12" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/13" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/14" ) { //�޶�����3��֮��ʹ����Ч
		tell_object(me,HIY "�����ʹ��ͻȻ��һ�������г��֣�һ��ץ�������е����ӣ������������Ѿ������˰ɣ���˵�꽫���������ˡ�\n"NOR);
		destruct(this_object());	
		return 1;
	} else {
		tell_object(me, HIC "�㿴����ζ�����ӣ���Ҳ����һ���̽��˶��\n" NOR);     	
		delete(LAST_GIFT_USER, me);//ɾ���ϴ����������ɵĲ��������ӱ��β�����ȷ��ÿλ���ֻ����һ�Ρ�
		set(THIS_GIFT_USER, 1, me);
		set("gift_dw", (CHINESE_D->chinese_time(7, ctime(time()))), me);
		addn("combat_exp", 10000, me);
		addn("potential", 10000, me);
		addn("max_neili", 100, me);
		addn("max_jingli", 100, me);
		tell_object(me,HIC "��о��Լ����巢�������Եı仯���������ˣ�\n" NOR);     	
		destruct(this_object());
	}
	return 1;
}

void owner_is_killed() { destruct(this_object()); }
