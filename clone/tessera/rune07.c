//rune07.c

// Tal ��

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune07", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����Խ��������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 7);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "ref_jing"   : 60,
                ]));
                set("enchase/armor_prop", ([
                        "ref_jing"   : 30,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
