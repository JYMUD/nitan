// toukui.c ͷ��
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "�ҿ�ͷ��" NOR, ({ "jiakang toudai", "jiakang", "toudai" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIY "���ǵ´��ҿ������е�ͷ���������С��´����ҿ���������\n" NOR);
                set("value", 350000);
                set("armor_prop/int", 5);
        }
        setup();
}

int query_autoload()
{
        return 1;
}