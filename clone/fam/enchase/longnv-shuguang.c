inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "��Ů�����" NOR, ({"longnv shuguang", "longnv", "shuguang" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "��Ů������˶�����������򰵣��޹�������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "��Ů�����");
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

