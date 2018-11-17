// Npc: /d/shaolin/npc/seng-bing3.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("守寺僧兵", ({
                "seng bing",
                "seng",
                "bing",
        }));
        set("long",
                "他是一位身材高大的壯年僧人，兩臂粗壯，膀闊腰圓。他手持兵\n"
                "刃，身穿一襲灰布鑲邊袈裟，似乎有一身武藝。\n"
        );

        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiaji", 50);
        set("combat_exp", 10000);
        set("score", 1);

        set_skill("force", 50);
        set_skill("hunyuan-yiqi", 50);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("unarmed", 50);
        set_skill("banruo-zhang", 50);
        set_skill("parry", 50);
        set_skill("blade", 50);
        set_skill("cibei-dao", 50);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("unarmed", "banruo-zhang");
        map_skill("parry", "cibei-dao");
        map_skill("blade", "cibei-dao");

        setup();

        carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/cloth")->wear();
}

void init()
{
        object me, ob;
        mapping fam;

        ::init();

        ob = this_player();
        me = this_object();
        
        if (interactive(ob) 
         && !query("no_fight", environment(ob) )
        && !present("yingxiong ling", ob) 
         && ((fam=query("family", ob)) && fam["family_name"] != "少林派") )
        {
                if( !query_temp("warned", ob)){
                        command("say 你是誰？  怎麼闖到少林寺里來了？！");
                        command("say 快給我速速離開，下次看到決不輕饒！");
                        set_temp("warned", 1, ob);
                }
                else if( query_temp("stay", ob)<10)addn_temp("stay", 1, ob);
                else {
                        command("say 大膽狂徒，竟敢闖到少林寺里來撒野！！！\n");
                        me->set_leader(ob);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
                }
        }       

}