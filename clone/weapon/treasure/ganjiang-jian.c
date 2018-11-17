// ganjiang-jian.c 幹將劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name( HIC "幹將劍" NOR , ({ "ganjiang jian", "jian", "sword" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long","這就是赫赫有名的幹將劍，劍鋒上隱隱透出一股清氣，仔細凝望，只覺一股肅殺之氣森然外散。\n");
                set("value", 20000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中，頓時風沙飛揚，黑雲罩日，漫天神鬼驚懼。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘，一下子風平浪靜，晴空萬里。\n");
        }
        init_sword(130);
        setup();
}
