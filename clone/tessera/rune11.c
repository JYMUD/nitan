//rune11.c

// Amn ��ķ

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune11", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�ҫ����Ʈ�������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 11);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_metal"    : 24,
                ]));
                set("enchase/armor_prop", ([
                        "reduce_metal"    : 8,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
