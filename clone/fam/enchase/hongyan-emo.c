inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "���۶�ħ" NOR, ({"hongyan emo", "hongyan", "emo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ��ͨ��ı�ʯ�������ħ�����顣\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "���۶�ħ");
                set("enchase/point", 1);
                set("enchase/type", "all");
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

