#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "����ѥ" NOR, ({ "feima xue2", "feima", "xue2" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIW "һ˫���������˼亱���ı�ѥ�ӣ��̲��������������\n");
                set("value", 2000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 3); //������+1
                                set("armor_prop/int", 2); //��������+2
                set("material", "boots");
                                set("limit", ([
                                        "exp"  :  30000000,
                                        "dex"  :  60,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
