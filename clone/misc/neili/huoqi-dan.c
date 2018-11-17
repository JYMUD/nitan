#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "火氣丹" NOR, ({"huoqi dan", "huoqi", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 50000);
                set("only_do_effect", 1);
                set("long", HIY "一顆紫色的藥丸。恢復2000點內力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if (time() - me->query_temp("last_eat") < 2)
        {
                write("你剛服用過葯，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        me->set_temp("last_eat", time());

        message_vision(HIW "$N吃下一顆火氣丹，感到內力有所補充。\n" NOR, me);

        if (me->query("max_neili") - me->query("neili") < 2000)
                  me->set("neili", me->query("max_neili"));
        else
                  me->add("neili", 2000);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}
