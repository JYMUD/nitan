#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "�׻�����" NOR, ({"bai hu", "metal"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIY "��������Ƕ10LV�����Խ�\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}
