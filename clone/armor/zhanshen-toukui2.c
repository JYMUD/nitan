// toukui.c ͷ��
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "ս��ͷ��" NOR, ({ "zhanshen toukui2", "zhanshen", "toukui2" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIM "����һ�����Ƶ�ͷ�������Ա���ͷ����\n" NOR);
                set("value", 1500000);
                set("armor_prop/armor", 200);
        }
        setup();
}

int query_autoload()
{
        return 1;
}