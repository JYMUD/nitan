inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "������" NOR, ({"jiangjun ling", "jiangjun", "ling"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "һ���ɫ�����ƣ�������С��´���������������\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
