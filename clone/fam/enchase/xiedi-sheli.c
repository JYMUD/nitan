inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "а������" NOR, ({"xiedi sheli", "xiedi", "sheli" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "��˵��а�����������ɢ������ʹ�â��\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "а������");
                set("enchase/point", 1);
                  set("enchase/type", "def");
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

