#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIM "���߻���" NOR, ({ "wuzhe huwan2", "wuzhe", "huwan2" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "һ˫��ʿ�õĻ���\n" NOR);;
                set("unit", "˫");
                set("value", 500000);
                set("armor_prop/armor", 200);
                                set("armor_prop/str", 5);
                set("limit", ([
                        "exp"    :    8000000,
                        "str"    :    40,
                        "int"    :    40,
                ]));                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
