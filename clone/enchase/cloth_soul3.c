#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "ս��֮��" NOR, ({"cloth soul3", "cloth", "soul3"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "����һ��ս��֮�ꡣ\n" NOR);
                set("unit", "��");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "cloth");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

