#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "���Ƥ��" NOR, ({ "xiangbian pige", "xiangbian", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM  "����һ�ű���ͨ͸��Ƥ�������ʱ����������ߵľ��Ѳ��ϡ�\n" NOR);
                set("base_unit", "��");
                set("unit", "��");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}