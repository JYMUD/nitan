
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIC "��ħ֮��" NOR, ({ "jianmo zhiyu2", "zhiyu2", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "�����ɶ������ȡ�����ë�����������ɵ�ͷ�Σ������ƺ��̺��˸������ѧ���С�\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 35);
                set("armor_prop/str", 35);
                set("armor_prop/con", 35);
                set("armor_prop/damage", 4000);
                set("armor_prop/sword", 80);
                set("special/desc", "��Ч�����ȼ����80����");
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}