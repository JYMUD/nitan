#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "��ɽ��ˮͼ" NOR, ({ "gaoshan tu", "gaoshan", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "��ɽ��ˮ�ľ���");
                set("can_tattoo", ({ "���"}));
                set("tattoo_type", ({ "��������" }));
                                set("tattoo_addneili", -3000);
                                set("tattoo_addjingli", 600);
                                set("scborn", 1);
        }
}
