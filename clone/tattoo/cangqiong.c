#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "����»�ͼ" NOR, ({ "cangqiong tu", "cangqiong", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "��嫵������¹Ҹ߿�");
                set("can_tattoo", ({ "�ؿ�"}));
                set("tattoo_type", ({ "��" }));
                set("tattoo_dex", 6);
                                set("tattoo_special", "agile");
                set("tattoo_spcname", "�������");
                                set("scborn", 1);
        }
}
