
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "��ħ" HIC "֮��" NOR, ({ "jianmo zhiyu6", "zhiyu6", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "�����ɶ������ȡ�����ë�����������ɵ�ͷ�Σ������ƺ��̺��˸������ѧ���С�\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 50);
                set("armor_prop/str", 50);
                set("armor_prop/con", 50);
                set("armor_prop/damage", 7000);
                set("armor_prop/sword", 300);
                set("special/desc", "��Ч�����ȼ����300����");
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