 inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "�׻ơ�ս��" NOR, ({"yanhuang zhanshen", "yanhuang", "zhanshen" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "�׻ơ�ս�����׻�֮��Ʒ��ӵ���������������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�׻ơ�ս��");
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

