#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIB "����ָ��" NOR, ({ "heiyu zhihuan", "heiyu", "zhihuan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIB "����ǧ����������ɵ�ָ�����������ȣ������򺮣�����������⹦Ч��\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 1000);
                set("armor_prop/int", 10);
                set("armor_prop/add_tihui_xiaolv", 5); // ������ἳȡЧ��5% jiqu.c�д���
                set("special/desc", HIR "����ʵս��ἳȡЧ��5%��" NOR);
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

