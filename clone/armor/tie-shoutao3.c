// shoutao.c  ����

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "������" NOR, ({ "tie shoutao3", "tie", "shoutao3" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIW "����һ˫������������ף������ƺ���Ӳ��̹��ĺۼ���\n" NOR);
                set("value", 350000);
                set("material", "tie");
                set("armor_prop/armor", 100);
                set("armor_prop/unarmed_damage", 500);
        }
        setup();
}

int query_autoload()
{
        return 1;
}