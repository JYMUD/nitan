#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name( HIR "��Ѫ�ɻ�" NOR, ({ "hongxue feihun2", "hongxue2" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("value", 2000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 12);
                                set("armor_prop/damage", 300);
                                set("limit", ([ 
                                        "exp" : 5000000,
                                        "scborn" : 1,
                                ]));
                set("material", "gold");
        }
        setup();
}

int query_autoload()
{
        return 1;
}
