#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "大內丹" NOR, ({"danei dan", "danei", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 10000);
                set("only_do_effect", 1);
                set("long", HIY "一顆紫色的藥丸。恢復800點內力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat", me)<2 )
        {
                write("你剛服用過葯，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat", time(), me);

        message_vision(HIW "$N吃下一顆大內丹，感到內力有所補充。\n" NOR, me);

        if( query("max_neili", me)-query("neili", me)<800 )
                  set("neili",query("max_neili",  me), me);
        else
                  addn("neili", 800, me);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}