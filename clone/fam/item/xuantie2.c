#include <ansi.h>

inherit ITEM;

void create()
{
         set_name(NOR + CYN "��ɽ������ǿ��" NOR, ({ "tianshan xuantie2", "tianshan", "xuantie" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "���伫Ϊ������������������ɽ�����ּ�Ϊ���ء�\n" NOR);
                set("unit", "��");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "��ɽ����" NOR);
                set("can_make", "all");
                                set("not_make", ({ "����","����"}));
                                 set("power_point", 160);
        }
}

int query_autoload()
{
        return 1;
}

