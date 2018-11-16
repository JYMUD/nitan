
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIM "ת��ѫ�£�������" NOR, ({ "kongming xunzhang", "kongming", "xunzhang" }));
        set("long", HIM "ת�����õ�ѫ�£��ϻ�ǧ�ֹ���������˼ͼ���������������Ǿ��¡�\n" NOR);
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
                set("armor_prop/unarmed", "apply_armor() * 3");
                set("armor_prop/finger", "apply_armor() * 3");
                set("armor_prop/strike", "apply_armor() * 3");
                set("armor_prop/hand", "apply_armor() * 3");
                set("armor_prop/cuff", "apply_armor() * 3");
                set("armor_prop/claw", "apply_armor() * 3");
                set("special/desc", HIR "��Īаʥ�����������Ƕ������п��ּ�����Ч�ȼ���" NOR); 
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