

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�ջ�" NOR, ({ "penglai juhua" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("long", HIY "����һ��ջ���������ֳ����ֲ�ͬ����ɫ����˵ֻ�������ɵ����С�\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}