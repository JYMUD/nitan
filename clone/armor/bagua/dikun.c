
#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name(HIY "���Ե���ѥ" NOR, ({ "dikun xue", "dikun", "xue" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"�׻Ʒ���ʮ�������װ֮�����Ե���ѥ\n" NOR);
                set("unit", "˫");
                set("value", 100);
                set("armor_prop/dex", 20);
                set("armor_prop/T_bagua", 1); // ��װ������־
        }
        setup();
}

int query_autoload()
{
        return 1;
}