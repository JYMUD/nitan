#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("釣竿", ({ "diao gan", "diao", "gan" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根樺木製的釣竿，製作得頗為奇特。\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
                set("shaolin",1);
        }
        init_club(35);
        setup();
}
