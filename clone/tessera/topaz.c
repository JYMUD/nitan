
#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "�Ʊ�ʯ" NOR, ({ "topaz" }));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "����һ�ű�ʯ�������ƺ�����ĳ�������ħ����\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("level", 2); 
                set("material", "topaz"); 
                set("no_identify", 1);
        }
        setup();
}

