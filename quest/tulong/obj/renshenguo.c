// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR"�˲ι�"NOR, ({"guo", "renshen guo"}));
        set("unit", "��");
        set("long", "����һֻ�˲ι�, �Ѿ�����, ����������ܲ�����С����\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
        if(arg=="guo")
        {
                addn("max_neili", 10, me);
                set("neili",query("max_neili",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                message_vision("$N����һö�˲ι���ֻ���þ���������Ѫ��ӯ����������ԴԴ�������������ٸе������ɿ�!\n",me);

                destruct(this_object());
        }
        return 1;
}
