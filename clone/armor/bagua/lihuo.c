
#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(HIY "��������" NOR, ({ "lihuo jia", "lihuo", "jia" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮����������\n" NOR);
                set("unit", "��");
                set("value", 100);
                set("armor_prop/armor", 1000);
                set("armor_prop/T_bagua", 1); // ��װ������־
        }
        setup();
}

int query_autoload()
{
        return 1;
}
