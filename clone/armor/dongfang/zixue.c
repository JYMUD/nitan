#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(MAG "��Ѫ��" NOR, ({ "zixue huan", "zixue", "huan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", MAG "��������ɫѪ�������ɣ����ֱ���̹ǣ�����������⹦Ч��\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 1000);
                set("armor_prop/int", 10);
                set("armor_prop/add_tihui_gift", 5); // ������ά��5% giftd.c�д���
                set("special/desc", HIR "ɱ�֡�ɱBOSS������ά����������5%��" NOR);
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

