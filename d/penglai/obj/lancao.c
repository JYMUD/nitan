

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "����" NOR, ({ "penglai lancao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("long", HIY "����һ�����ݣ���״�����أ��ƺ����˼�δ��������\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}