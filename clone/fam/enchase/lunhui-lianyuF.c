inherit ITEM;
#include <ansi.h>

void create()
{
         set_name(HIW "�ֻء�����" NOR, ({"lunhui lianyu","lunhui","lianyu" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                  set("long", HIW "�ֻ�֮�ࡤ����Ϊ�ס�\n" NOR);
                set("unit", "��");
                set("value", 5000);
                 set("enchase/name", "�ֻء�����");
                 set("enchase/point", 90);
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

