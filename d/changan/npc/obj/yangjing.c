//yangjing.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"������"NOR, ({"yangjing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "��");
                set("value", 2000);
        }

        setup();
}

int init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me = this_player();
        if (! id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if (me->is_busy())
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");
                message_vision("$N����һ��" + name() + "��\n", me);

        if( query("eff_jing", me)/query("max_jing", me)<0.9 )
        {
                me->receive_curing("jing",query("max_jing", me)/50);
        }
        me->start_busy(2);
        destruct(this_object());
        return 1;
}