inherit ITEM;
#include <ansi.h>
void create()
{
        set_name("花粉袋", ({ "huafen dai", "dai"}) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "氣味芳香的花粉袋\n");
                set("value", 1000);
        }
}
