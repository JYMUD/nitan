
#include <ansi.h>
#include <armor.h>

inherit RINGS;

void create()
{
        set_name(HIY "���Կ�ˮ��" NOR, ({ "kanshui huan", "kanshui", "huan" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮�����Կ�ˮ��\n" NOR);
                set("unit", "ö");
                set("value", 100);
                set("armor_prop/int", 10);
                set("armor_prop/T_bagua", 1); // ��װ������־
        }
        setup();
}

int query_autoload()
{
        return 1;
}