inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "��Ů֮��" NOR, ({"longnv zhilei", "longnv", "zhilei" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "��˵��Ů֮���˶���С��Ů���������ɣ�ӵ�����������޷����ܵ�������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "��Ů֮��");
                set("enchase/point", 200);
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

