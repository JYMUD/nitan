#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "������ľ" NOR, ({"qing long", "wood"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "��������Ƕ10LV������ľ��\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}
