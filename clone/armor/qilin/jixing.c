#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIR "�����롤����" NOR, ({ "jixing xue", "jixing", "xue" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIR "����һ˫ͨ�����ѥ�ӣ�ɢ����������Ϣ�Ĺ�â��\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //������+60
                set("material", "boots");
                set("limit", ([
                        "exp"  :  50000000,
                        "dex"  :  80,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
