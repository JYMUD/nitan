#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "�϶�����ͼ" NOR, ({ "change tu", "cange", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "�϶��µ�ͼ��");
                set("can_tattoo", ({ "����"}));
                set("tattoo_type", ({ "��ò" }));
                set("tattoo_per", 5);
                                set("scborn", 1);
        }
}
