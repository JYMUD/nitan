inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "�׻�֮��" NOR, ({"yhhero" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIG "�׻�֮�����׻�֮��Ʒ���㽫����������ȴ���������������µĸо���\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�׻�֮��");
                set("enchase/point", 200);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 90);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

