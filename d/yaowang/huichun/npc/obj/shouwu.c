#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT"������"NOR, ({"heshou wu", "heshou", "wu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ó������εĺ����ڡ�\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
