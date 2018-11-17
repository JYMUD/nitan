// pink_cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>;
#include <ansi.h>;
inherit CLOTH;

void create()
{
        set_name(HIM"粉紅綢衫"NOR, ({"hong choushan", "pink cloth", "cloth"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"這件粉紅色的綢衫上面綉着幾隻黃鵲，聞起來還有一股淡香。\n");
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}
