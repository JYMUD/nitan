#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "��Ӣ�ƽ�ѫ��" NOR, ({ "jingying gold medal", "jingying", "xunzhang" }));
        set("long", HIY "��ɽ�۽���Ӣ���һ��õ�ѫ�£��ǳ������ǿ�ߵ�������\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 200);
                set("armor_prop/practice_times", 200);
                set("armor_prop/derive_times", 200);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}