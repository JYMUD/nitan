#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "Ӣ��ѫ��" NOR, ({ "hero medal", "hero", "xunzhang", "medal" }));
        set("long", HIR "ɱ���ܻ�ڶ�������ѫ�£���Ӣ�۵�������\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 500);
                set("armor_prop/practice_times", 500);
                //set("armor_prop/derive_times", 500);
        }
        set("auto_load", 1);
        setup();
}
