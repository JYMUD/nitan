

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "��÷��" NOR, ({ "penglai qingmeijiu" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "ƿ");
                set("value", 1);
                set("long", HIY "����һƿ�������Ƶ���÷�ƣ���Ȼװ��ƿ�У�ȴ��Ȼ�޷��ڸ���������\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}