
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIG "��ȸ��" NOR, ({ "kongque ring", "kongque", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "��ȸ���������ȸ֮���������š����ݡ���\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/dex", 20);
                set("armor_prop/damage", 200);
        }
        setup();
}

int query_autoload()
{
        return 1;
}