#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "ӨѪ��˿ͼ" NOR, ({ "zhusi tu", "zhusi", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "��������֩������Ѫ��ɫ��˿");
                set("can_tattoo", ({ "��"}));
                set("tattoo_type", ({ "����" }));
                set("tattoo_int", 10);
                                set("tattoo_str", -8);
                                set("tattoo_per", -4);
                                set("scborn", 1);
        }
}
