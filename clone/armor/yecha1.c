
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIY "ҹ��" NOR, ({ "yecha fu", "yecha", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIY "����һ�ŵ��������滭��һ�����صĹ�֣���Ի��ҹ�档\n" NOR);
                set("value", 95000);
                set("limit", ([
                        "exp"    :   500000,
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