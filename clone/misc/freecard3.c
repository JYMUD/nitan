// card.c
#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIY "��ʮ����������" NOR, ({"fee free card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",HIY "����һ�ż�ֵ��ʮ�����ƽ�Ľ���������������³����Խ���Ӧ��ֵ�ķ��ݡ�\n" NOR);
                set("value", 1);
                                set("fee free", 500000);
                set_weight(100);
        }
        setup();
}

int query_autoload()
{
        return 1;
}