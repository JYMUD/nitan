#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "�۽�����ѫ��" NOR, ({ "lunjian silver medal", "lunjian", "xunzhang" }));
        set("long", HIW "��ɽ�۽����µڶ���õ�ѫ�£��ǳ������ǿ�ߵ�������\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 150000);
                set("material", "silver");
                set("armor_prop/research_times", 300);
                set("armor_prop/practice_times", 300);
                //set("armor_prop/derive_times", 300);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}
