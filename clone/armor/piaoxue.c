#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "Ʈѩ" NOR, ({ "piao xue", "piao", "xue" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 400000);
                                set("special/desc", HIW "���������Ч�Ṧ10����" NOR);
                                set("armor_prop/dex", 20);
                                set("armor_prop/str", -7);
                set("armor_prop/dodge", 10);
                                set("limit", ([ 
                                        "exp" : 2000000,
                                        "dex" : 40, 
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
