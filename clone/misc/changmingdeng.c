#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "������" NOR, ({ "changmingdeng for xueyi"}) );
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "\n����һյ�����ƣ�Ϊѩ�������Ϊѩ����·��Ը��˳��ͨ�����֮·��\n NOR");
                set("value", 1);
                set("unit", "յ"); 
                set("no_get", 1);                
        }
}
