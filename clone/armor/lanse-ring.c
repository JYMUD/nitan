
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIC "��ɫ����" NOR, ({ "lanyao ring", "lanyao", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "��ɫ���������صĻ��������š��ǻۡ���\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/int", 10);
                set("armor_prop/damage", 200);        
        }
        setup();
}

int query_autoload()
{
        return 1;
}