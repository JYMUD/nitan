
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(NOR + WHT "��������ѫ��" NOR, ({ "silver medal" }));
        set("long", NOR + WHT "2005��μ��׻�9.18��ɱ���ܲ�����Ǿ��ļ���ѫ�¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);
                set("armor_prop/medal2", 1);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}