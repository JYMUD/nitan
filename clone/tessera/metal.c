// metal.c ����

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����" NOR, ({ "jing jin", "metal" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIW "����һö��������������֮��������ɣ�ɫ���ף��᲻�ɴݡ�\n" NOR);
                set("value", 2000);
                set("unit", "ö");
                set("magic/element", "metal");
        }
        setup();
}
