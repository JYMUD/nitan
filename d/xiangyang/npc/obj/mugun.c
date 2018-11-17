// mugun.c

#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("木棍", ({ "mu gun", "club", "gun" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "這是一桿木匠做的木棍，手工相當精細。\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N從腰帶里抽出一桿$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰帶上。\n");
        }
        init_club(3);
        setup();
}