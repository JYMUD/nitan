// card.c
#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIC "������������" NOR, ({"fee free card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",HIC "����һ�ż�ֵ�������ƽ�Ľ���������������³����Խ���Ӧ��ֵ�ķ��ݡ�\n" NOR);
                set("value", 1);
                                set("fee free", 30000);
                set_weight(100);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
