

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "�����걾" NOR, ({ "hudie biaoben" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("long", HIM "���ǵ�������ȥ�ĺ������ɵı걾��\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}