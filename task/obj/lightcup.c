#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIB "夜光杯" NOR,({"yeguangbei"}));
    set_weight(300);
        if( clonep() )
            destruct(this_object());
        else {
        set("long", "一個盛滿了鮮紅如血的葡萄美酒的夜光杯。\n");
                set("unit", "個");
        set("value", 0);
        set("max_liquid", 10);
        } 
        set("owner","華赫艮");
        set("liquid", ([
        "type": "alcohol",
        "name": "葡萄美酒",
                "remaining": 5,
        "drunk_apply": 20,
        ]) );
        setup();
}       
