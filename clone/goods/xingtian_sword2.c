

// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
 
void create()
{
        set_name(HBGRN "����ħ��" NOR, ({ "xingtian sword", "sword" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "�������������ʹ�õ�ħ��������Ѫ����졣\n" NOR);
                set("value", 3000); 
                set("no_sell", "����������������\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }     

        set("mod_mark", "A2034");
        set("mod_level", "M2030");
        set("mod_name", HBRED "������װ" NOR);
        init_sword(50000);
        set("quality_level", 3);
        
        setup();
}

