#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "��ʦ�����" NOR, ({ "tianshi charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "�˷��ľ��б��������������ʧ֮���ܣ���������ǰ�������ϡ�\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("no_sell", 1);
                set("auto_load", 1);
        }
        setup();
}

