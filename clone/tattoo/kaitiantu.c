#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "����ٵ�ͼ" NOR, ({ "kaitian tu", "kaitian", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "�̹ſ���ٵصľ���");
                set("can_tattoo", ({ "�ұ�"}));
                set("tattoo_type", ({ "�˺��ȼ�" }));
                                set("tattoo_damage", 100);
                                set("scborn", 1);
        }
}
