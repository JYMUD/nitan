// xitang.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR"ϲ��"NOR, ({"xi tang", "tang"}));
        set("unit", "��");
        set("value",10000);
        set("long", "����һ������ϲ�ǡ�\n");
        set("amount",100);
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
        if(arg=="xi tang" || arg=="tang")
        {
                message_vision(NOR"$N��һ��"HIR"ϲ��"NOR"�Ը����⣬�����������������������ܰ��\n",me);

                destruct(this_object());
        }
        return 1;
}