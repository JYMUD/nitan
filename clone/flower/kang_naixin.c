// kan_naixin.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIW "康乃馨" NOR, ({"kangnaixin", "kang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一朵素凈端立的康乃馨，代表溫馨，真摯的情感。\n");
                set("unit", "束");
                set("base_value", 35);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"