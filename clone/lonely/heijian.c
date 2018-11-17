#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + WHT "黑劍" NOR, ({ "hei jian", "jian", "hei", "sword" }));
        set_weight(6200);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "這是一柄黑色的寶劍，劍身發出陰寒之氣，令人"
                            "毛骨悚然。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "抽出一柄黑色的寶劍，頓覺寒氣彌"
                               "漫於四周。\n" NOR);
                set("unwield_msg", HIC "$N" HIC "劍轉三周，插劍入鞘，寒氣隱於"
                                   "劍鞘之中。\n" NOR);
                set("stable", 100);
        }                                                                                                                    
        init_sword(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "yinyang-ren" 
           || me->query_skill("yinyang-ren", 1) < 100)
                return damage_bonus / 2;   
              
        if(random(8) == 4)
        {
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIG "\n$N" HIG "踏前一步，手中" HIB "黑劍" HIG 
                       "一抖，平平刺出，$n" HIG "頓覺一股寒氣撲面而"
                       "來。\n" NOR;
        }
        return damage_bonus;
}