
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIG "��ħ֮��" NOR, ({ "jianmo zhiyu4", "zhiyu4", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "�����ɶ������ȡ�����ë�����������ɵ�ͷ�Σ������ƺ��̺��˸������ѧ���С�\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 38);
                set("armor_prop/str", 38);
                set("armor_prop/con", 38);
                set("armor_prop/damage", 5200);
                set("armor_prop/sword", 180);
                set("special/desc", "��Ч�����ȼ����180����");
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