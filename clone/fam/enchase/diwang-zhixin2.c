inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "����֮��" NOR, ({"diwang zhixin", "diwang", "zhixin" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "����֮��");
                set("enchase/point", 30);
                set("enchase/type", "waist");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

