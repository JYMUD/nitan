

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "�������" NOR, ({ "penglai pantao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("long", HIM "����һ��������ң���˵ÿ������Ž����\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}