// tiejia.c ����
//

#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(NOR + WHT "������" NOR, ({ "gangtie kai3", "gangtie", "kai3" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                                set("value", 300000);
                set("armor_prop/armor", 300);
                                set("armor_prop/parry", 20);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
