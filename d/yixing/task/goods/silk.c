// /d/yixing/task/goods/silk.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN"綢緞"NOR, ({ "silk" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一匹做工極其考究的綢緞。\n");
                set("unit", "匹");
                set("value", 1000);
                set("material", "silk");
        }
        setup();
}