
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIR "����֮��" NOR, ({ "huoyan ring", "huoyan", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIR "�ɻ�����ľ��ǻû����ɵĽ�ָ�������Ż���Ĺ�â������������\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/dex", 20);
                set("armor_prop/str", 20);
                set("armor_prop/int", 20);
                set("armor_prop/con", 20);
                set("armor_prop/damage", 2000);

                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));

        }
        setup();
}

int query_autoload()
{
        return 1;
}