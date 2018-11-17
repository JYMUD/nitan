#include <weapon.h>
#include <ansi.h>
 
inherit THROWING;
 
void create()
{
        set_name(HIC "回龍璧" NOR, ({ "huilong bi", "huilong", "bi" }));
        set_weight(100);
        if (clonep()) 
                set_default_object(__FILE__); 
        else {
                set("long", HIC "一支溫瑩剔透的玉壁，上面雕紋着一條蛟龍。\n" NOR);
                set("unit", "支");
                set("value", 80000);
                set("no_sell", 1);
                set("material", "stone");
                set("base_unit", "支");
                set("base_weight", 100);
                set("base_value", 1000);
        }
        set_amount(1);
        init_throwing(120);
        setup();
}