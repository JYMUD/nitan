
#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIW "�ɻ�ս��" NOR, ({ "shihun zhanyi"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "һ�������ս�£�ͨ��͸����Ʈ���������ƺ��������˼䡣\n" NOR);
                set("material", "steel");
                set("value", 1);
                set("armor_prop/armor", 100);
                set("armor_prop/str", 5);
                set("armor_prop/con", 5);
        }
        setup();
}

