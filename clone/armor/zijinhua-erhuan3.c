
#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIR "�Ͻ𻨶���" NOR, ({ "zijinhua erhuan3", "zijinhua", "erhuan3" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/armor", 1);
                set("armor_prop/dex", 10);
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