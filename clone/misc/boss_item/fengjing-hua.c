inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "��ʿɽ�羰��" NOR, ({"fengjing hua", "fengjing", "hua"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "����һ�����Ÿ�ʿɽ�羰��ͼ����\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
