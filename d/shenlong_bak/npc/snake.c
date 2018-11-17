// /d/shenlong/npc/snake.c
// Last Modified by winder on Jul. 12 2002

inherit NPC;
int snake_attspeed(object);

void create()
{
        set_name("毒蛇", ({ "snake", "she" }) );
        set("race", "爬蛇");
        set("age", 4 + random(10));
        set("long", "一隻有着三角形腦袋的蛇，尾巴沙沙做響。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("cor", 30);

        set("qi", 300);

        set("combat_exp", 5000 + random(5000));

        set_temp("apply/attack", 15+random(10));
        set_temp("apply/damage", 6+random(10));
        set_temp("apply/armor", 2+random(10));

        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        victim->apply_condition("snake_poison", 20 + random(40) +
                victim->query_condition("snake_poison"));
}

#include "snake.h"
