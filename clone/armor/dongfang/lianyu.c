
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(MAG "����" HIR "Ѫ��" NOR, ({ "lianyu xuehuan", "lianyu", "xuehuan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", MAG "�Ϻ�ɫ��ָ����Ѫɫ�İ��ƣ�ɢ������������֮����������������� \n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 4000);
                set("armor_prop/int", 20);
                set("armor_prop/add_tihui_gift", 5); // ������ά��5% giftd.c�д���
                set("armor_prop/add_tihui_xiaolv", 5); // ������ἳȡЧ��5% jiqu.c�д���
                set("special/desc", HIR "ɱ�֡�ɱBOSS������ά����������5%��" 
                                        "����ʵս��ἳȡЧ��5%"NOR);
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

