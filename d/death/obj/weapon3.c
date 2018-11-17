#include <ansi.h>
#include <weapon.h>

inherit CLUB;

void create()
{
        set_name(HIR"天雷神擋" NOR, ({ "tianlei shendang","tianlei","shendang", "dang" }));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("value", 1200000);
                set("material", "steel");
                set("long", "一桿上古神木所鑄造的棍子，乃不世之神兵。\n");
                set("wield_msg", "$N提起$n握在手中，威風凜凜。\n");
        }
        init_club(120);
        setup();
}

