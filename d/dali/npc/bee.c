// bee.c 毒蜂
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("毒蜂", ({ "dufeng", "bee" }) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 20);
        set("long", "一隻色彩斑斕大個野蜂，成群結隊的。\n");
        set("attitude", "aggressive");
        set("shen_type", -1);

        set("limbs", ({ "蜂嘴","蜂腰","蜂翅","尾刺" }) );
        set("verbs", ({ "bite", "sting" }) );

        set("combat_exp", 500);
        set("neili",80);
        set("max_neili",80);
        set("jingli",50);
        set("max_jingli",50);

        set_temp("apply/attack", 20);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 10);
        setup();
}
