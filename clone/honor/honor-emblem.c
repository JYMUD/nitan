#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "����ѫ��" NOR, ({ "honor emblem", "emblem" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "һö����ѫ�£��������ߵ�������\n" NOR);
                set("unit", "ö");
                set("value", 500000);
        }
        setup();
}
