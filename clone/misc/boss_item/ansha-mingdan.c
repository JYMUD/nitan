inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "��ɱ����" NOR, ({"ansha mingdan", "ansha", "mingdan"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "����һ��д�г�͢ҪԱ���ֵİ�ɱ������\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
