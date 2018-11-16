
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIR "ҹ��" NOR, ({ "yecha fu", "yecha", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIR "����һ�ŵ��������滭��һ�����صĹ�֣���Ի��ҹ�档\n" NOR);
                set("value", 95000);
                set("limit", ([
                        "exp"    :   2000000,
                        "str"    :   60,
                        "con"    :   50,
                ]));
                set("apply_prop/damage", 100);
                set("armor_prop/unarmed_damage", 100);
                set("armor_prop/int", 2);
                set("armor_prop/str", 2);
        }
        setup();
}

int query_autoload()
{
        return 1;
}