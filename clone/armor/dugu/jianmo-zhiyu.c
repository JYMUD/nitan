
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "��ħ֮��" NOR, ({ "jianmo zhiyu", "zhiyu", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "�����ɶ������ȡ�����ë�����������ɵ�ͷ�Σ������ƺ��̺��˸������ѧ���С�\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 30);
                set("armor_prop/str", 30);
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/sword", 50);
                set("special/desc", "��Ч�����ȼ����50����");
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