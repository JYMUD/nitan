inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + MAG "������ʯ" NOR, ({"tianyu shi", "tianyu", "shi"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "һ���������Ϲ��ʯͷ���ƺ��̲��Ų�Ѱ����������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "������ʯ");
                set("enchase/point", 30);
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

