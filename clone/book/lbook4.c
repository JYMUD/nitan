// literateb4.c 九章算術
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"「九章算術」"NOR, ({ "literateb4", "shu4", "book4"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","一本讀得很破舊的《九章算術》。\n");
                set("value", 5000);
                set("material", "paper");
                set("skill", ([
                        "name": "literate",
                        "exp_required": 10000,
                        "jing_cost":    10,
                        "difficulty":   25,
                        "max_skill":   119,
                        "min_skill":   110,
                ]) );
        }
}