// hua4.c
//
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIC "�����" NOR, ({"hua4", "feicui"}));
        set("unit", "��");
        set("long", "����һ��ǧ���ѵ�һ�������������˵�ܽ�ٶ���\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");
        set_temp("nopoison", 1, this_player());
        set("eff_jing",query("max_jing",  this_player()), this_player());
        set("jing",query("max_jing",  this_player()), this_player());
        set("eff_qi",query("max_qi",  this_player()), this_player());
        set("qi",query("max_qi",  this_player()), this_player());
        tell_object(this_player(), HIG "��ֻ��һ�����������ķΣ���ʱ��̨һƬ������������ˬ��\n" NOR );
        destruct(this_object());
        return 1;
}