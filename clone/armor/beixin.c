// beixin.c
// Last Modified by winder on May. 29 2001

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name( "鐵背心", ({ "tie beixin", "beixin" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 15);
                set("shaolin",1);
        }
        setup();
}