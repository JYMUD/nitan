inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "����֮��" NOR, ({"qilin zhihun", "qilin", "zhihun" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "����֮��");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 5]) );  // ÿ������о�Ч��5%
        }
        setup();
}

int query_autoload()
{
        return 1;
}
