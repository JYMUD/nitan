
#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIW "��������" NOR, ({ "yinyang erhuan", "yinyang", "erhuan" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/armor", 1);
                set("armor_prop/force", 20);
                set("armor_prop/con", 5);
                set("limit", ([
                        "sex" : 3, // 1 Ϊ����
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}