// water.c ����

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "����" NOR, ({ "xuan bing", "water" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "����һ�����������������ɽ���У�ɫ���ڣ��������ˡ�\n" NOR);
                set("value", 2000);
                set("unit", "��");
                set("magic/element", "water");
        }
        setup();
}
