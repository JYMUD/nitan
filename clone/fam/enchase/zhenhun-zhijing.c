inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "���֮��" NOR, ({"zhenhun zhijing", "zhenhun", "zhijing" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "���֮��");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 10); // ������10���׵�ʱ�򷽿���Ƕ
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 10]) );  // ÿ������о�Ч��10%
        }
        setup();
}

int query_autoload()
{
        return 1;
}

