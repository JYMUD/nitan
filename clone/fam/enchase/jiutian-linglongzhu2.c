inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "����������" NOR, ({"linglong zhu", "linglong", "zhu"}));
        set_weight(2000);
        set("long", HIM "����ƽ�������ӣ�Ĵָ���С����ȴ���Ը���ʱ���ı仯�������ͬ����ɫ�������ޱȡ�\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "����������");
                set("enchase/point", 1);
                set("enchase/type", "surcoat");
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

