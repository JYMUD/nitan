#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "��������ͼ" NOR, ({ "wenqu tu", "wenqu", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "�������·���ͼ��");
                set("can_tattoo", ({ "�ؿ�"}));
                set("tattoo_type", ({ "����" }));
                set("tattoo_int", 6);
                                set("addqianneng", 10000);
                                set("scborn", 1);
        }
}
