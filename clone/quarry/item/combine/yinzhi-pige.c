#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + WHT "����Ƥ��" NOR, ({ "yinzhi pige", "yinzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT  "һ�ŷ��������Ƥ����������µ��Ϻò��ϡ�\n" NOR);
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