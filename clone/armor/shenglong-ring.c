
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "ʥ��֮Ȫ" NOR, ({ "shenglong ring", "shenglong", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "ʥ��֮Ȫ�˹�������ʥ��֮���������š���������\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 20);
                set("armor_prop/damage", 200);
        }
        setup();
}

int query_autoload()
{
        return 1;
}