//rune26.c

// Vex ����˹

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune26", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�ԨͨԪ���������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 26);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "avoid_parry" : 20, 
                ]));
                set("enchase/armor_prop", ([
                        "avoid_force" : 5,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
