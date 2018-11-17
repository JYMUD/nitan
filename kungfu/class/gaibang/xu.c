// xu.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("徐長老", ({"xu zhanglao", "xu", "zhanglao"}));
        set("gender", "男性");
        set("age", 85);
        set("long", "白須飄動，穿着一身補丁累累的鶉衣，是個年紀極高的老丐。\n");
        set("title", "丐幫九袋長老");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);
        set("no_get", "1");

        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);

        set("combat_exp", 100000);
        set("score", 20000);

        set_skill("force", 95);            // 基本內功
        set_skill("huntian-qigong", 90);   // 混天氣功
        set_skill("hand", 90);             // 基本手法
        set_skill("suohou-hand", 85);      // 鎖喉擒拿手
        set_skill("staff", 90);            // 基本杖法
        set_skill("fengmo-zhang", 85);     // 瘋魔杖法
        set_skill("dodge", 90);            // 基本躲閃
        set_skill("xiaoyaoyou", 95);       // 逍遙遊
        set_skill("parry", 85);            // 基本招架
        set_skill("staff", 90);            // 基本棍杖
        set_skill("strike",85);  // 基本掌法
        set_skill("lianhua-zhang",85); // 蓮花掌
        set_skill("dragon-strike",85);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");

        map_skill("force", "huntian-qigong");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");
        map_skill("hand", "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("hand", "suohou-hand");

        //set("party/party_name", HIC"丐幫"NOR);
        //set("party/rank", RED"九袋長老"NOR);
        //set("party/level", 9);
        create_family("丐幫", 18, "長老");

        setup();

        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走開，我不收徒。");
}
