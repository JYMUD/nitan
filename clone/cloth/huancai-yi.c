//baipao.c
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIM "�ò���" NOR, ({"huan caiyi", "huan", "caiyi"}));
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "����ֻӦ�����У�\n");
                set("material", "silk");
                set("armor_prop/armor", 1000);
                set("value",100);
        }
        setup();
}
