inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + BLU "�پ�" NOR, ({"wu jing", "wu", "jing"}));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + BLU "һ�鿴����ͨ�Ŀ�������ںڣ�Ͷ�������������Ϣ��\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�پ�");
                set("enchase/point", 40);
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

