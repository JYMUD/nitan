#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "���ɷ���ͼ" NOR, ({ "longfeng tu", "longfeng", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "����˫�ɵľ���");
                set("can_tattoo", ({ "�ұ�"}));
                set("tattoo_type", ({ "���еȼ�" }));
                                set("tattoo_attack", 100);
                                set("scborn", 1);
        }
}
