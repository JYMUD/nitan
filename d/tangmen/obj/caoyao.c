inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "tun");
}

void create()
{
        set_name("��ҩ", ({"cao yao","cao","yao"}));
        set("unit", "��");
        set("long", "����һ����ͨ�Ĳ�ҩ��\n");
        setup();
}

int do_eat(string arg)
{
if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
if(arg=="yao") 
{
tell_object(this_player(), HIG "��ֻ��һ�����������ķ�,��ʱ��̨һƬ����,������ˬ��\n" NOR );
set_temp("nopoison", 1, this_player());
set("eff_jingli",query("max_jingli",  this_player()), this_player());
set("jingli",query("max_jingli",  this_player()), this_player());
set("eff_qi",query("max_qi",  this_player()), this_player());
set("qi",query("max_qi",  this_player()), this_player());
destruct(this_object());
}
return 1;
}