// Obj: /d/lingxiao/obj/guaishexue.c
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

int do_drink(string);
void init();

void init()
{
        add_action("do_drink", "drink");
        remove_call_out("decay");
        call_out("decay", 180);
}

void create()
{
        set_name( HIR "怪蛇血" NOR , ({"she xue", "blood"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "管");
                set("long", "一管怪蛇的血液，很是腥臭，看起來綠油油的。\n");
                set("value", 1000);
                set("drug_type", "補品");
        }
        set("is_monitored",1);
        set("no_put",1);
        setup();
}

int do_drink(string arg)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;
        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);
 
        if(!id(arg)) return notify_fail("你要喝什麼？\n");
        if(!present(this_object(), this_player()))
                return notify_fail("你要喝什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢喝，小心別嗆着了。\n");

        if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 5, me);
                message_vision( HIR"$N只覺一股熱線從咽喉直通到腹中，然後丹田就象有一團火般燒了起來。\n" NOR, me);
        }
        destruct(this_object());
        return 1;
}

void decay()
{
        object where = environment(this_object());
        if ( interactive(where) )
                message("vision", MAG"竹管啪的一聲破了，蛇血流出弄得你一身甚是腥臭。\n"NOR, 
                        where); 
        else
                message("vision", MAG"竹管啪的一聲破了，蛇血流了一地。\n"NOR,
                        where);
        destruct(this_object());
}