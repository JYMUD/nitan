#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIY "���" NOR, ({ "head" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "cloth");
                set("armor_prop/armor", 100);
        }
        setup();
}
void owner_is_killed()
{
        destruct(this_object());
} 