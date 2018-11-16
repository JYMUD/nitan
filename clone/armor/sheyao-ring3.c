
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIR "����ָ��" NOR, ({ "sheyao ring", "sheyao", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "����ָ���Ǵ�˵���߾������ָ����ӵ�����ص�������\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/dex", 10);
                set("armor_prop/str", 8);
                set("armor_prop/int", 8);
                set("armor_prop/con", 10);
                set("armor_prop/damage", 400);
                set("armor_prop/magic_find", 20);

                set("limit", ([ 
                         "exp" : 12000000,
                         "scborn" : 1,
                ]));

        }
        setup();
}

int query_autoload()
{
        return 1;
}
