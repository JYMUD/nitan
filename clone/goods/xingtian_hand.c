// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit HANDS;
 
void create()
{
        set_name(HBGRN "����ħ��" NOR, ({ "xingtian hand", "hand" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "���������ʹ�ù������ƣ�ͨ��Ѫ�����졣\n" NOR);
                set("value", 3000); 
                set("no_sell", "����������������\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("armor_prop/armor", 10);
                set("armor_prop/unarmed_damage", 50000);
        }
        
        set("mod_mark", "A2037");
        set("mod_level", "M2030");
        set("mod_name", HBRED "������װ" NOR);
        set("quality_level", 3);

        setup();
}

