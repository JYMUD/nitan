// yushou.c

#include <ansi.h>
#include <armor.h>
inherit WRISTS;

void create()
{
        set_name(CYN"������"NOR, ({"yu shouzhuo", "shouzhuo" }));
        set_weight(500);
        set("taskobj", 1);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "�����ɵ�����������������Բ������\n");
                set("unit", "ö");
                set("value", 0);
                set("material", "gold");
                set("armor_prop/armor", 10);
        }
        setup();
}
