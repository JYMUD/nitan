
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "��ħ֮��" NOR, ({ "jianmo zhiyu5", "zhiyu5", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "�����ɶ������ȡ�����ë�����������ɵ�ͷ�Σ������ƺ��̺��˸������ѧ���С�\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 40);
                set("armor_prop/str", 40);
                set("armor_prop/con", 40);
                set("armor_prop/damage", 6000);
                set("armor_prop/sword", 240);
                set("special/desc", "��Ч�����ȼ����240����");
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