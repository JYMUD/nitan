inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "���鱦��" NOR, ({"tianshu baoling", "tianshu" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "���鱦��");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 12); // ������12���׵�ʱ�򷽿���Ƕ
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_jiqu" : 15]) );  // ÿ������о�Ч��15%
        }
        setup();
}

int query_autoload()
{
        return 1;
}

