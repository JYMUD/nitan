inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "�� �� ʯ" NOR, ({"diling shi", "diling", "shi" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "�� �� ʯ");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 12); // ������12���׵�ʱ�򷽿���Ƕ
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 15]) );  // ÿ������о�Ч��15%
        }
        setup();
}

int query_autoload()
{
        return 1;
}

