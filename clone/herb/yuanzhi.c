#include "herb.h"

void create()
{
        set_name(NOR + HIB "遠志" NOR, ({ "yuan zhi", "yuan", "zhi", "herb_yuanzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIB "遠志是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 3000);
                set("base_weight", 75);
        }
        setup();
}