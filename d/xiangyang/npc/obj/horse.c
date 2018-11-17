// horse
#include <ansi.h>

inherit NPC;
// inherit F_UNIQUE;

void create()
{
        set_name(HIC "青驄馬" NOR, ({ "horse"}));
        set("race", "家畜");
        set("gender", "雄性");
        set("age", 2+random(3));
        set("long", "這是一匹回部寶馬，日行千里，夜行八百。\n"+
                "玩家可以騎上它去指定的地方(ride)。\n");
        set("ridable", 1);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "腹部", "尾巴","後腿","前腿" }) );
        set("verbs", ({ "bite","hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);
        set_temp("is_rided_by","tuo lei");

        setup();
}