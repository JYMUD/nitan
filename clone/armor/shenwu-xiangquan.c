// necklace.c ������

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIY "������Ȧ" NOR, ({ "shenwu xiangquan", "shenwu", "xiangquan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/armor", 300);
        }
        setup();
}        

int query_autoload()
{
        return 1;
}