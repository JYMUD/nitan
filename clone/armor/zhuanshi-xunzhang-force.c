
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIY "ת��ѫ�£�Ǭ����" NOR, ({ "qiankun xunzhang", "qiankun", "xunzhang" }));
        set("long", HIY "ת�����õ�ѫ�£��ϻ�Ǭ��ͼ���������������Ǿ��¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/con", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/force", "apply_armor() * 3");
                set("special/desc", HIR "��Īаʥ�����������Ƕ�����Ч�ڹ��ȼ���" NOR); 
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