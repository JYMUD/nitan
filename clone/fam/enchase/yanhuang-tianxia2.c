inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "�׻ơ���������" NOR, ({"junlin tianxia", "junlin", "tianxia" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "�׻ơ������������׻�֮��Ʒ���㽫����������ȴ���������������µĸо���\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�׻ơ���������");
                set("enchase/point", 220);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

