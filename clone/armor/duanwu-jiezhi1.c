
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIC "ʮ���ꡤ���硤����" NOR, ({ "duanwu longjie", "longjie" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIC "�������׻�ʮ�����߶���ڷ��ŵĽ�ָ����ɢ�������˵��̹⣬�����һ������֮��\n" NOR);
                set("value", 100);
                set("material", "gold");
                set("armor_prop/dex", 10);
                set("armor_prop/str", 10);
                set("armor_prop/int", 10);
                set("armor_prop/con", 10);
                set("armor_prop/damage", 500);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
