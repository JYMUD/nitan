inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "�׻ơ���ɫ����" NOR, ({"guose tianxiang", "guose", "tianxiang" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "�׻ơ���ɫ�������׻�֮��Ʒ���������ģ�ֻ������͸����������˵Ĺ�â��\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�׻ơ���ɫ����");
                set("enchase/point", 160);
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

