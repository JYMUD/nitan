#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIC"����"NOR, ({"box"}) );
        set_weight(300);
        set_max_encumbrance(80000000);
        set("unit", "Щ");
        set("long", "һ��ɢ�������ع�â�ı��䣬������Դ�(open)����\n");
        set("closed", 1);
        set("no_get", 1);
        set("base_value", 200);
        set("base_unit", "��");
        set("BAOXIANG_LIST",([ 
                "/clone/money/gold":200,   //��Ʒ�ļ���:���� 
                "/clone/money/silver":300,   //��Ʒ�ļ���:����
                "/clone/money/coin":500,   //��Ʒ�ļ���:����
        ]));
 
        set_amount(1);
} 

void init()
{
        add_action("do_open", "open");
}
