inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "�챦ʯ" NOR, ({"hong baoshi1", "baoshi1" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ�ź�ɫ�����ı�ʯ�����˼���Ʒ��\n" NOR);
                set("unit", "��");
                set("value", 50000);
                set("enchase/name", "�챦ʯ");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 90);
                                //set("nine_object", 1); // �ſ���Ƕ��Ʒ���
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

