inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "��Ů���̺�����" NOR, ({"bihao shenlong", "bihai", "shenlong" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "��Ů���̺������˶���֮����ɢ���ű���ɫ�ķ�â��\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "��Ů���̺�����");
                set("enchase/point", 190);
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

