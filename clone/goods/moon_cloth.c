// This program is a part of NT MudLIB
// moon.c ����

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "����" NOR, ({ "moon soul", "moon" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "̫��������۶��ɣ��°�ɫ�������Ķ��񣬰�а���֡���\n" NOR);
                set("value", 50000);
                set("unit", "��");
                set("can_enchant", "armor");
                set("auto_load", 1);
        }
        set("enchase",  ([ /* sizeof() == 5 */
                "armor_prop" : ([ /* sizeof() == 3 */
                        "research_effect" : 3,
                        "derive_effect"   : 3,
                        "practice_effect" : 3,
                ]),
                "type" : "cloth",
                "SN" : 1 + random(9),
        ])) ;

        set("enchant", 1);
        set("set_data", 1);
        setup();
}

