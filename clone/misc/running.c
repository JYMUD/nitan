// trans_cart.c
//

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "�����С���" NOR, ({ "running" }));
        set_weight(200000);
        set_max_encumbrance(1000000);
        set("running", 1);
        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                set("long", "�����ڿ����ϱ��� ����\n");
                set("unit", "��");
                set("material", "air");
                set("no_get", "!@#$!@#%%^@!^\n");
        }
        setup();
}
