
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIM "�׻Ƽ���ѫ��" NOR, ({ "jinian medal" }));
        set("long", HIM "����һö�׻ƹٷ����͵ļ���ѫ�£�������Щ���׻Ʒ�չ�������׵���ҡ�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 3);
                set("armor_prop/dex", 3);
                set("armor_prop/str", 3);
                set("armor_prop/int", 3);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}