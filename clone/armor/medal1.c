
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIY "�ƽ�����ѫ��" NOR, ({ "gold medal" }));
        set("long", HIY "2005��μ��׻�9.18��ɱ���ܲ���ùھ��ļ���ѫ�¡�\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 200);
                set("armor_prop/con", 10);
                set("armor_prop/dex", 10);
                set("armor_prop/str", 10);
                set("armor_prop/int", 10);
                set("armor_prop/medal1", 1);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}