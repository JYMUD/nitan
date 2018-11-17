// dongjinkui.c
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("董金魁", ({ "dong jinkui", "dong" ,"jinkui"}));
        set("gender", "無性");
        set("title", HIC"慈寧宮太監"NOR);
        set("age", 26);
        set("per", 20);
        set("long", "一個壯碩漢子，挺胸凸肚，架勢頗為不善。\n");

        set("combat_exp", 30000);
        set("shen_type", 0);

        set_skill("unarmed", 50);
        set_skill("blade", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        
        set_temp("apply/attack", 35);
        set_temp("apply/defense", 35);
        set_temp("apply/damage", 20);

        set("chat_chance", 10);
        set("chat_msg", ({
              (: random_move :),
        }));

        setup();
        add_money("silver", random(10));
        carry_object(__DIR__"obj/tjcloth")->wear();
}
