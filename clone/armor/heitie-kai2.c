

#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIB "������" NOR, ({ "heitie kai2", "heitie", "kai2" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 600);
                                set("limit", ([
                                        "exp"  :  3000000,
                                        "str"  :  40,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
