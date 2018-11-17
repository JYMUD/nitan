// shoutao.c  手套

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "鐵手套" NOR, ({ "tie shoutao3", "tie", "shoutao3" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIW "這是一雙鋼鐵鑄造的手套，上面似乎有硬物刻過的痕迹。\n" NOR);
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