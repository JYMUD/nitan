
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "�콵��������" NOR, ({ "xingshi huan2" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIY "��˵�к����������ָ����\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/unarmed", 100);
                set("armor_prop/magic_find", 8);
                set("special/desc", "��Чȭ���ȼ����100����\n"+
                                    "��Чȭ�ŵȼ����100����\n"+
                                    "��Ч�Ʒ��ȼ����100����\n"+
                                    "��Чָ���ȼ����100����\n"
                );
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
