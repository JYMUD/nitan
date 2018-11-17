// gangzhang.c 鋼杖

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("鋼杖", ({ "gangzhang" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根粗重的鋼杖，是星宿派專用之物。\n");
                set("rigidity", 150); 
                set("value", 1500);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_staff(40);
        setup();
}

