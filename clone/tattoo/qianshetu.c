#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "ǧ�߲���ͼ" NOR, ({ "qianshe tu", "qianshe", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "����ֻ���߲��Ƶ�ͼ��");
                set("can_tattoo", ({ "��"}));
                set("tattoo_type", ({ "��" }));
                set("tattoo_dex", 10);
                                set("tattoo_con", -6);
                                set("scborn", 1);
        }
}
