// wood.c ľ��

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "ľ��" NOR, ({ "mu ling", "wood" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "����һƬľ�飬���Զ�����ɣ֮�����Ϲ��������ܣ�ÿǧ�����ľ������ɫ�࣬��֮�����\n" NOR);
                set("value", 2000);
                set("unit", "Ƭ");
                set("magic/element", "wood");
        }
        setup();
}
