#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "披风之魂" NOR, ({"surcoat soul3", "surcoat", "soul3"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "这是一个披风之魂。\n" NOR);
                set("unit", "个");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "surcoat");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

