#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"������"NOR, ({"yangjing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 2000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N����һ��" + name() + "��\n", me);

        if( query("eff_jing", me)<query("max_jing", me) )
        {
                me->receive_curing("jing",query("max_jing", me)/50);
        }
        me->start_busy(2);
        destruct(this_object());
        return 1;
}
