// �ǻ�ˮ�� ��ͬ��ϵͳ���� �ο��ļ� help mater

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "�ǻ�ˮ��" NOR, ({ "zhihui shuijing" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "һ���ɫ��ˮ����Ƭ�����ͬ����ϲ����\n" NOR);
                set("value", 1);
                set("unit", "��");
        }
        setup();
}

int query_autoload() { return 1; }
