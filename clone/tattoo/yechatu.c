#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "ҹ������ͼ" NOR, ({ "yecha tu", "yecha", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "ҹ�������ģ��");
                set("can_tattoo", ({ "��"}));
                set("tattoo_type", ({ "����" }));
                set("tattoo_str", 10);
                                set("tattoo_dex", -8);
                                set("scborn", 1);
        }
}
