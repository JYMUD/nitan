

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIB "ҹ����" NOR, ({ "yexing yi", "yexing", "yi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIB "һ����ɫ��ҹ���£���������������������ӯ��\n" NOR);
                set("material", "cloth");
                set("value", 800000);
                set("armor_prop/armor", 100);
                set("armor_prop/dodge", 10);
                set("special/desc", HIR "������Ч�Ṧ10����"); 
                set("limit", ([
                        "exp"  :  1200000,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
