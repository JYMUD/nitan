#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIM "���߻���" NOR, ({ "wuzhe huwan3", "wuzhe", "huwan3" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "һ˫��ʿ�õĻ���\n" NOR);;
                set("unit", "˫");
                set("value", 500000);
                set("armor_prop/armor", 200);
                                set("armor_prop/str", 8);
                set("limit", ([
                        "exp"    :    22000000,
                        "str"    :    50,
                        "int"    :    50,
                ]));                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
