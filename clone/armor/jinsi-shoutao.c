// shoutao.c  ����

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "��˿����" NOR, ({ "jinsi shoutao", "jinsi", "shoutao" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIW "����һ˫��˿������ɵ����ף�����������\n" NOR);
                set("value", 750000);
                set("material", "gold");
                set("armor_prop/armor", 500);
                set("armor_prop/unarmed_damage", 600);
                set("limit", ([
                        "exp"    :  200000,
                        "int"    :  38,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}