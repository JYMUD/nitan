#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("王誠", ({ "wang cheng", "wang", "cheng"}));
        set("title", "日月神教風雷旗主");
        set("long", @LONG
這是日月神教風雷旗主王誠，此人身材矮胖，
滿臉堆笑，其實為人十分狠毒。
LONG);
        set("gender", "男性" );
        set("class", "scholar");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        
        set("max_qi", 4500);
        set("max_jing", 3500);
        set("neili", 3200);
        set("max_neili", 3200);
        set("jiali", 120);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 160);
        set_skill("riyue-xinfa", 160);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("blade", 160);
        set_skill("danding-dao", 160);
        set_skill("parry", 150);
        set_skill("cuff", 150);
        set_skill("zhenyu-quan", 150);
        set_skill("claw", 150);
        set_skill("poyue-zhao", 150);
        set_skill("martial-cognize", 150);
        set_skill("literate", 160);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "riyue-xinfa");
        map_skill("blade", "danding-dao");
        map_skill("parry", "danding-dao");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        set("coagents", ({
                ([ "startroom" : "/d/heimuya/chengdedian",
                   "id"        : "ren woxing" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "皺眉道："
                                "我不管你是怎麼上來的，這黑木崖豈"
                                "是自由進出之地？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？還不快快給我放"
                                "下！" NOR,
        ]));

        create_family("日月神教", 14, "旗主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.kou" :),
                (: perform_action, "cuff.tong" :),
                (: perform_action, "claw.duan" :),
                (: exert_function, "recover" :),
        }) );
        set("master_ob",3);
        setup();

        carry_object("/d/heimuya/npc/obj/jinpao")->wear();
        carry_object("clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

             command("say 我不收徒，你去找教內的其餘長老好了。");
}
