
#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIY "������ɽ��" NOR, ({ "genshan dai", "genshan", "dai" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮��������ɽ��\n" NOR);
                set("unit", "��");
                set("value", 100);
                set("armor_prop/damage", 1000);
                set("armor_prop/T_bagua", 1); // ��װ������־
        }
        setup();
}

int query_autoload()
{
        return 1;
}