inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "���ɲ���" NOR, ({"gusong canjue", "gusong", "canjue"}));
        set_weight(2000);
        set("long", NOR + YEL "������ͨ����ʯ��ȴ�̲��������������\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "���ɲ���");
                set("enchase/point", 7);
                set("enchase/type", "medal2");
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

