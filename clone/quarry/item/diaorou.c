#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "貂肉" NOR, ({ "diao rou", "diao", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊散發著腥臊臭的貂肉。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 60);
        }
        setup();
        set_amount(1);
}