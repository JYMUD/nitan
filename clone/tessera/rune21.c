//rune21.c

// Pul ��

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "����" NOR, ({"rune21", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�̫�����ط������Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 21);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "learn_effect"  : 20,
                ]));
                set("enchase/armor_prop", ([
                        "learn_effect"  : 5,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
