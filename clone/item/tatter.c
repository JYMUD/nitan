#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "��Ƥ��Ƭ" NOR, ({ "sheepskin tatter", "tatter" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "����һ��ǳ����ϵ���Ƥ��Ƭ��������в�ȱ��ȫ����������ͼ����\n" NOR);
                set("unit", "ö");
                set("value", 500000);
        }
        setup();
}
