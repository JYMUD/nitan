
#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIY "������Ǭ��" NOR, ({ "tianqian guan", "tianqian", "guan" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮��������Ǭ��\n" NOR);
                set("unit", "��");
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