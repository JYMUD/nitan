#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "������ͼ��Ƭ-32" NOR, ({ "diwang suipian32", "diwang", "suipian" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "��˵���ϹŻƵۣ��׵ۼ�������µ�ͼ����Ƭ�����β�ȱ��ȫ���ƺ�������ʲô�ر�ġ�\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_drop", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}