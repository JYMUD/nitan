
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIW "ǧ�ֹ���" NOR, ({ "qianshou guanyin", "qianshou", "guanyin" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIW "һ�����ư��Сǧ�ֹ���������ԭ����֮������\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/fy", 4);

        }
        setup();
}

int query_autoload()
{
        return 1;
}