
#include <ansi.h>
#include <armor.h>

inherit RINGS;

void create()
{
        set_name(HIY "八卦坎水環" NOR, ({ "kanshui huan", "kanshui", "huan" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"炎黃風雨十年紀念套裝之：八卦坎水環\n" NOR);
                set("unit", "枚");
                set("value", 100);
                set("armor_prop/int", 10);
                set("armor_prop/T_bagua", 1); // 套裝計數標誌
        }
        setup();
}

int query_autoload()
{
        return 1;
}