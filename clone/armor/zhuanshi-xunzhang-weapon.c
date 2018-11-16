
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(NOR + WHT "ת��ѫ�£�������" NOR, ({ "benliu xunzhang", "benliu", "xunzhang" }));
        set("long", NOR + WHT "ת�����õ�ѫ�£��ϻ���ˮ����ͼ���������������Ǿ��¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/str", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/whip", "apply_armor() * 3");
                set("armor_prop/club", "apply_armor() * 3");
                set("armor_prop/staff", "apply_armor() * 3");
                set("armor_prop/dagger", "apply_armor() * 3");
                set("armor_prop/hammer", "apply_armor() * 3");
                set("armor_prop/axe", "apply_armor() * 3");
                set("special/desc", HIR "��Īаʥ�����������Ƕ��߳�������������б���������Ч�ȼ���" NOR); 
                set("limit", ([
                        "scborn" : 1, 
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}