

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL + GRN "��Ҷ" NOR, ({ "penglai songye" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "Ƭ");
                set("value", 1);
                set("long", YEL + GRN "����һƬ�ӳ����������µ���Ҷ��\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}