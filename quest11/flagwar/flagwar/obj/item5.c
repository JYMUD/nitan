#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"����ս - "HIW"���׷�"NOR, ({"fwar count seal","seal"}) );
        set_weight(300);
        set("unit", "��");
        set("long", "����սר��������Ʒ����������������ʱ���Զ�ʹ�á�\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}