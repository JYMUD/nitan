#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "�콵�����ѥ" NOR, ({ "kuangfeng xue2" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIW "����һ˫��������֮Ƥ�Ƴɵ�ѥ�ӣ���˵���Ϻ��������硣\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //������+60
                set("armor_prop/dodge", 200);
                set("special/desc", "��Ч�Ṧ�ȼ����200����");
                set("material", "boots");
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
