#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "��" HIM "��" HIC "����" NOR, ({ "foguang baozhu", "foguang", "baozhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ����ҫ�ŷ��ı��飬��â���䣬�˼亱�С�\n" NOR);
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