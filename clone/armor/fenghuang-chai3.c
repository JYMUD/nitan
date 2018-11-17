
#include <armor.h>
#include <ansi.h>

inherit HAIRPIN;

void create()
{
        set_name(HIR "鳳凰金釵" NOR, ({ "fenghuang chai3", "fenghuang", "chai3" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/armor", 1);
                set("armor_prop/int", 3);
                set("armor_prop/con", 5);
                set("limit", ([
                        "sex" : 1, // 1 為女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}