inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "è��ʯ" NOR, ({"maoyao shi", "maoyao", "shi" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "è��ʯ");
                set("enchase/point", 1);
                set("enchase/type", "surcoat");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

