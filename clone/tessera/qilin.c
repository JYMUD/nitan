#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(YEL "���롤��" NOR, ({"qi lin", "earth"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", YEL "��������Ƕ10LV����������\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}