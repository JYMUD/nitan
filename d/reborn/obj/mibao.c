// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM "�ܱ�����" NOR, ({ "mibao qizhen" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "����һ���ܱ����䡣\n" NOR);

        }
        setup();
}
