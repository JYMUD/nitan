inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "���䱦ʯ" NOR, ({"zhenwu baoshi", "zhenwu", "baoshi" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "���䱦ʯ");
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

