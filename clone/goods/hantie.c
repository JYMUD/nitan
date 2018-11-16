#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "����������" NOR, ({"ice steel", "han tie", "tie"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "һ���������Ľ�������˵�����Ϲ�����������\n"
                                "���ĺ�����ӵ�������ħ�����Ϲ�����Ѿ�\n"
                                "ͨ�顣\n" NOR);
                set("value", 10000000);
                set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "water");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_water" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
