#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "���鵤" NOR, ({ "jueqing dan", "jueqing", "dan" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����һ���ʺ�ɫ�ĵ�ҩ�����������������˵�ܽ��黨֮����\n" NOR);
                set("value", 500000);
                set("unit", "��");             
        }
        setup();
}

int query_autoload()
{
        return 1;
}