//rune30.c

// Berؐ

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune30", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ���¡��ʤ�������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 30);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "attack"        : 400,              
                ]));
                set("enchase/armor_prop", ([
                        "defense"       : 100,   
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
