#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIG "��" HIW "��" HIM "����" HIY "ѥ" NOR, ({ "qicai xue", "qicai", "xue" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIC "����һ˫�����߲ʹ�â�ı�ѥ����˵���ǲ��Զ�����\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //������+60
                set("armor_prop/int", 10); //
                set("armor_prop/damage", 1000); 
                set("material", "boots");
                set("limit", ([
                        "exp"  :  100000000,
                        "dex"  :  80,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
