inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "Ļ��ʯ" NOR, ({"mutian shi", "mutian", "shi"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "Ļ��ʯ");
                set("enchase/point", 100);
                set("enchase/type", "waist");
                set("enchase/cur_firm", 100);
                set("nine_object", 1); // �ſ���Ƕ��Ʒ���
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

