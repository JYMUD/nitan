
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC "��֮��" NOR, ({ "haizhi xin3", "haizhi", "xin3" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 200);
                set("armor_prop/str", 5);
        }
        setup();
}        

int query_autoload()
{
        return 1;
}