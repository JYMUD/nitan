#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIB "���䡤ˮ" NOR, ({"xuan wu", "water"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB "��������Ƕ10LV������ˮ��\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}
