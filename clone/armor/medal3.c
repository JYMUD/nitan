
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIG "��ͭ����ѫ��" NOR, ({ "bronze medal" }));
        set("long", HIG "2005��μ��׻�9.18��ɱ���ܲ���ü����ļ���ѫ�¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 2);
                set("armor_prop/dex", 2);
                set("armor_prop/str", 2);
                set("armor_prop/int", 2);
                set("armor_prop/medal3", 1);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}