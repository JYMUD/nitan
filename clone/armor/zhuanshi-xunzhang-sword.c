
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;


void create()
{
        set_name(HIG "ת��ѫ�£��񽣣�" NOR, ({ "shenjian xunzhang", "shenjian", "xunzhang" }));
        set("long", HIG "ת�����õ�ѫ�£��ϻ��񽣴���ͼ���������������Ǿ��¡�\n" NOR);
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
                set("armor_prop/sword", "apply_armor() * 3");
                set("special/desc", HIR "��Īаʥ�����������Ƕ�����Ч�����ȼ���" NOR); 
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