#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIR "��ȸ����" NOR, ({"zhu que", "fire"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "��������Ƕ10LV�����Ի�\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1); 
        }
        setup();
}
