// jinchuang.c 金創葯

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIY "金創葯" NOR, ({"jinchuang yao", "jinchuang", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包武林人士必備的金創葯。\n");
                set("value", 1000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (me->is_busy())
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不需要用金創葯。\n");
        else
        {
                me->receive_curing("qi", 50);
                message_vision("$N吃下一包金創葯，氣色看起來好多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}
