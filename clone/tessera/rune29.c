//rune29.c

// Sur ɪ

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({"rune29", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ����ϳ��ڷ������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 29);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "damage1"         : 3000,
                ])); 
                set("enchase/armor_prop", ([
                        "magic_find" : 5,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
