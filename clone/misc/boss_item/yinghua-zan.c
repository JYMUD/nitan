inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "��ӣ���ޡ�" NOR, ({"yinghua zan", "yinghu", "zan"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "����һ��д�С�ӣ���ޡ������ס�\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
