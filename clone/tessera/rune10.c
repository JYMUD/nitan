//rune10.c

// Thul 

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune10", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ����������������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 10);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "max_qi"    : 10000,
                ]));
                set("enchase/armor_prop", ([
                        "max_qi"    : 10000,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
