#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "Ʈѩ" NOR, ({ "piao xue2", "piao", "xue2" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 400000);
                                set("special/desc", HIW "���������Ч�Ṧ30����" NOR);
                                set("armor_prop/dex", 30);
                                set("armor_prop/str", -7);
                set("armor_prop/dodge", 30);
                                set("limit", ([ 
                                        "exp" : 35000000,
                                        "dex" : 60, 
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
