// fire.c �׾�

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED "�׾�" NOR, ({ "yan jing", "fire" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", RED "����һ���׾����ط��������������������ɫ��죬�¶ȼ��ߡ�\n" NOR);
                set("value", 2000);
                set("unit", "��");
                set("magic/element", "fire");
        }
        setup();
}
