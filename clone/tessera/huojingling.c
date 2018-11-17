#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIR "火之精靈・火" NOR, ({"huo jingling", "huo", "jingling"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "火神祝融之寶物，擁有着火屬性的最高力量。\n" NOR);
                set("unit", "塊");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("enchase/SN", 1 + random(9));
                set("enchase/cur_firm", 100); 
                set("enchase/type", "all");
                set("enchase/weapon_prop", ([
                        "add_fire" : 50,     
                        "add_skill" : 30,     
                ]));
                set("enchase/armor_prop", ([
                        "add_fire" : 50,     
                        "add_skill" : 30,     
                ]));
                set("magic/type", "fire");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
