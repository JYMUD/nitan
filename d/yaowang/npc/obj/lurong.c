#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( YEL "¹��" NOR , ({"lu rong", "rong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ֧÷��¹�ס�\n");
                set("unit", "֧");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}
