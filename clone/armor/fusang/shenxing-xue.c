#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIG "����ѥ" NOR, ({ "shenxing xue", "shenxing", "xue" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIG "���Է�ɣ���ı�ѥ����Ϊ����ɱ����������������������\n");
                set("value", 2000000);
                set("armor_prop/dex", 10); //������+1
                set("material", "boots");
                set("limit", ([
                        "exp"  :  9000000,
                        "dex"  :  40,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
