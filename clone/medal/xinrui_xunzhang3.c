#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIC "������ͭѫ��" NOR, ({ "xinrui bronze medal", "xinrui", "xunzhang" }));
        set("long", HIC "��ɽ�۽������������õ�ѫ�£��ǳ����������ǿ�ߵ�������\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 100000);
                set("material", "bronze");
                set("armor_prop/research_times", 100);
                //set("armor_prop/practice_times", 100);
                //set("armor_prop/derive_times", 100);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}