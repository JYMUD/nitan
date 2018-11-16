// This program is a part of NT MudLIB
// sun.c �ջ�

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(RED "�ջ�" NOR, ({ "sun soul", "sun" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", RED "̫��������۶��ɣ��ڽ�ɫ������а��ħ��ǧ�����ס���\n" NOR);
                set("value", 50000);
                set("unit", "��");
                set("can_enchant", "weapon");
                set("auto_load", 1);
        }

        set("enchase",  ([ /* sizeof() == 5 */
                "weapon_prop" : ([ /* sizeof() == 3 */
                        "research_effect" : 3,
                        "derive_effect"   : 3,
                        "practice_effect" : 3,
                ]),
                "type" : "club",
                "SN" : 1 + random(9),
        ])) ;

        set("enchant", 1);
        set("set_data", 1);
        setup();
}

