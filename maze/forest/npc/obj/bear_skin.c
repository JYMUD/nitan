#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("熊皮", ({ "xiong pi", "xiong", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "巨熊的皮毛，烏黑亮澤，手感極為光滑。\n" NOR);
                set("base_unit", "張");
                set("base_value", 7000);
                set("base_weight", 600);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}