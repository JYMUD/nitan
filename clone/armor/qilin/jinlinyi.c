

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIR "�����롤������" NOR, ({ "jinlin yi", "jinlin", "yi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "����һ���������£�������ҫ�Ž�ɫ�Ļ��棬Ѥ���ޱȡ�\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/armor", 2000);
                set("limit", ([
                        "exp"  :  50000000,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
