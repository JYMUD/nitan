inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "�����ظ��ͼ��" NOR, ({"anshouge tu", "anshouge", "tu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "����һ�Ż��з�ɣ���ظ���ε�ͼֽ��\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
