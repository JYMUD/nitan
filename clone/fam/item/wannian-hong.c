#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "�����" NOR, ({"wannian hong"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��������죬Ϊ��͢��Ʒ�����¼����ϳ˵����ϡ�\n" NOR);
                set("unit", "��");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}

