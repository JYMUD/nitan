#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�߾���Ƭ" NOR, ({"shejing linpian", "shejing", "linpian"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "һƬ���߾����ϻ�ȡ����Ƭ�������ߵ�������\n" NOR);
                set("unit", "Ƭ");
        }
}

int query_autoload()
{
        return 1;
}

