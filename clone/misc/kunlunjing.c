#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIW "���ؾ�" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIW "����һ��ͨ������ľ��ӣ���˵ӵ���ƿ�̫���������\n" NOR);
        }

        setup();
}

