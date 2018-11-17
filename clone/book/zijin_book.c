// zijin_book.c

#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(HIY"《紫金錘法》"NOR, ({ "zijin_book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本記述紫金錘法的書。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([ 
                        "name"        :  "zijin-chuifa",
                        "exp_required":  10000,
                        "jing_cost"   :  30,
                        "difficulty"  :  30,
                        "max_skill"   :  100,
                ]));
        }
}
