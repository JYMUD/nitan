
#include <armor.h>
#include <ansi.h>

inherit HAIRPIN;

void create()
{
        set_name(HIG "������" NOR, ({ "biyu chai", "biyu", "chai" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
                set("value", 200000);
                set("material", "stone");
                set("armor_prop/armor", 1);
                set("armor_prop/int", 2);
                set("limit", ([
                        "sex" : 1, // 1 ΪŮ��
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}