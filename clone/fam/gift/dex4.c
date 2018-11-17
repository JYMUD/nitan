#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIR "破陽無極仙丹Ⅱ型" NOR, ({ "wuji xiandan2" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此丹乃是天宮中的神品，凡人吃了可以平增身法。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 200000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "dex");
                set("gift_name", "先天身法");
                set("gift_point", 100);
                set("gift_msg", HIW "突然你只覺全身輕飄飄的，有股騰雲駕霧的感覺。\n" NOR);
        }
        setup();
}