inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "��ˮ�ڻ�" NOR, ({"bishui ronghua" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "��ˮ�ڻ�");
                set("enchase/point", 120);
                set("enchase/type", "wrists");
                                set("enchase/cur_firm", 100);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

