inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "����ʯ" NOR, ({"lan baoshi2", "baoshi2" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "һ����ɫ�����ı�ʯ�����˼���Ʒ��\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "����ʯ");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 100);
                                //set("nine_object", 1); // �ſ���Ƕ��Ʒ���
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

