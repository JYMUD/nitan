#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "�������ͼ" NOR, ({ "feixian tu", "feixian", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "Ⱥ�ɷ�����龰");
                set("can_tattoo", ({ "�β�"}));
                set("tattoo_type", ({ "����", "����", "����", "��" }));
                                set("tattoo_con", 2);
                                set("tattoo_dex", 2);
                                set("tattoo_str", 2);
                                set("tattoo_int", 2);
                                set("scborn", 1);
        }
}
