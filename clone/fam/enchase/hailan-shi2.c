inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "����ʯ" NOR, ({"hailan shi", "hailan", "shi" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "����֮����ǧ�����󡣾�˵�Ƕ�����Ů��ױ��\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "����ʯ");
                set("enchase/point", 1);
                set("enchase/type", "att");
                                set("enchase/cur_firm", 90);
                                set("nine_object", 1); // �ſ���Ƕ��Ʒ���
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

