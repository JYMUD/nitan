#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "��������" NOR, ({ "bipo xuantian", "bipo", "xuantian" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "���伫Ϊ�����ı�ʯ�������������ȡ�á�\n" NOR);
                set("unit", "��");
                set("value", 300000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", HIG "��������" NOR);
                set("can_make", "all");
                set("power_point", 150);
        }
}

int query_autoload()
{
        return 1;
}

