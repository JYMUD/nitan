
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name(HIY "���������" NOR, ({ "xunfeng yi", "xunfeng", "yi" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮�����������\n" NOR);
                set("unit", "��");
                set("value", 100);
                set("armor_prop/huibi", 1000);
                set("armor_prop/T_bagua", 1); // ��װ������־
        }
        setup();
}

int query_autoload()
{
        return 1;
}