inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "��Ů��ʴ" NOR, ({"longnv shi", "longnv", "shi" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��Ů��ʴ�����ɫ���˶���а�������������������ֲ���ĸо���\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "��Ů��ʴ");
                set("enchase/point", 180);
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

