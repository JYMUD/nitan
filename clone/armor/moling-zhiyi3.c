
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIG "ħ��֮��" NOR, ({ "moling zhiyi3", "moling", "zhiyi3" }) );
        set_weight(2000);
        set("long", HIG "����һ�����ƴ�˵�й������������磬������ʢ�����ˡ�\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                                set("value", 3000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/con", 8);
                                set("armor_prop/int", 8);
                                set("armor_prop/dodge", 40);
                                set("special/desc", HIR "������Ч�Ṧ40����");
                                set("limit", ([ 
                                        "exp" : 52000000,
                                        "scborn" : 1,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
