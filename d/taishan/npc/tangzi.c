// tangzi.c
// Last Modified by winder on Aug. 25 2001

inherit NPC;

void create()
{
        set_name("趟子手", ({ "tangzi shou","shou" }) );
        set("gender", "男性");
        set("age", 30);
        set("long", "這是個鏢局趟子手，長得虎背熊腰，一身橫練功夫。\n");
        set("combat_exp", 10000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("apply/attack", 20);
        set("apply/defense", 20);

        set("chat_chance", 5);
        set("chat_msg", ({
                "趟子手一聲大喊: 我～～武～～維～～揚～～！\n",
                (: random_move :)
        }) );

        set_skill("unarmed", 40);
        set_skill("sword", 20);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        setup();

        carry_object("/d/city/obj/duanjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/city/obj/jitui");

        add_money("silver", 1);
}