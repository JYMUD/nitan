
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIW "ת��ѫ�£��޼���" NOR, ({ "wuji xunzhang", "wuji", "xunzhang" }));
        set("long", HIW "ת�����õ�ѫ�£��ϻ�����޼�ͼ���������������Ǿ��¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/dex", 10);
                set("armor_prop/int", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/dodge", "apply_armor() * 2");
                set("armor_prop/parry", "apply_armor() * 2");
                set("special/desc", HIR "��Īаʥ�����������Ƕ�����Ч�Ṧ����Ч�мܵȼ���" NOR); 
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