// ����ʥˮ���ڿ��ױ���

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "����ʥˮ" NOR, ({ "bored water", "water" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һƿӨ��͸ʥˮ��ɢ���ѤĿ�Ĺ�ʡ�\n"
                            "������������󻯿��ױ�������ߡ�\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "ƿ");
        }

        setup();
}

int query_autoload()
{
        return 1;
}
