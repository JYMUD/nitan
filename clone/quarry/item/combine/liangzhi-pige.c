#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "����Ƥ��" NOR, ({ "liangzhi pige", "liangzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG  "����һ��ͨ��͸����Ƥ����������µ��Ϻò��ϡ�\n" NOR);
                set("base_unit", "��");
                set("unit", "��");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}