
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIW "���֮��" NOR, ({ "tiankong zhiyi3", "tiankong", "zhiyi3" }) );
        set_weight(2000);
        set("long", HIW "����һ����ɫ�����磬�ϻ�������ƣ�Ʈ��֮����\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                                set("value", 3000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 10);
                                set("armor_prop/int", 3);
                                set("armor_prop/dodge", 40);
                                set("special/desc", HIR "������Ч�Ṧ40����");
                                set("limit", ([ 
                                        "exp" : 18000000,
                                        "scborn" : 1,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
