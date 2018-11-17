// hook.c 鋼鉤

#include <weapon.h>;
inherit HOOK;

void create()
{
        set_name("鋼鉤", ({ "gang gou", "gou" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄特殊的精鋼劍，劍端帶着一個倒鉤。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回鞘中。\n");
        }
        init_hook(25);
        setup();
}