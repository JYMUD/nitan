#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + MAG "������Ʒ" NOR, ({"test object"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "����һ��������Ʒ����û�б���ʦ������Σ�ȴ���������Ϲ⡣\n" NOR);
                set("unit", "��");
                set("value", 1);
                                set("no_drop", 1);
                                set("no_sell", 1);
                                set("no_give", 1);
                                set("no_get", 1);
        }
}

int query_autoload()
{
        return 1;
}

