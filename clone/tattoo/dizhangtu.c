#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "�ز�ת��ͼ" NOR, ({ "dizhang tu", "dizhang", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "�ز�����ģ��");
                set("can_tattoo", ({ "��"}));
                set("tattoo_type", ({ "����" }));
                set("tattoo_con", 10);
                                set("tattoo_int", -7);
                                set("scborn", 1);
        }
}
