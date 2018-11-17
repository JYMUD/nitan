// Npc: /d/guiyun/npc/bee.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        set_name("蜜蜂", ({ "bee", "mifeng", "feng" }) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 2);
        set("long", "一隻飛來飛去的小蜜蜂。\n");
        set("attitude", "aggressive");
        set("combat_exp", 500);

        set_temp("apply/attack", 5);
        set_temp("apply/defense", 4);
        set_temp("apply/damage", 5);
        set_temp("apply/armor", 2);

        setup();
}
