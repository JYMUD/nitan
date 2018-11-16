
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIR "�����롤����" NOR, ({ "yanmie ring", "yanmie", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIR "���������Ϲ����ޣ�ӵ������������ֱ����һ�죬����ǿ������������\n"
                                "����֮ǰ��ŭԹ����һ˲�����۳ɵ�����֮�䣬�̺��˾޴��������\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 4000);
                set("armor_prop/magic_find", 20);

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
