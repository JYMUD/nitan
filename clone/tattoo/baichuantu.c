#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "�ٴ�����ͼ" NOR, ({ "baichuan tu", "baichuan", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "��ٴ����龰");
                set("can_tattoo", ({ "���"}));
                set("tattoo_type", ({ "��������" }));
                                set("tattoo_addneili", 2000);
                                set("tattoo_addjingli", -500);
                                set("scborn", 1);
        }
}
