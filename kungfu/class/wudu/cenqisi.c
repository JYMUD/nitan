#include <ansi.h>
#include "wudu.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("岑其斯", ({ "cen qisi", "cen", "qisi" }));
        set("nickname", HIR "五毒秀士" NOR);
        set("long", @LONG
他就是五毒教的右護法，人稱五毒秀士的岑其斯。
經常裝扮成一個白衣秀士的模樣，沒事總愛附庸風
雅。
LONG);
        set("title","五毒教護法");
        set("gender", "男性");
        set("age", 38);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 20);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("wudu-shengong", 120);
        set_skill("dodge", 110);
        set_skill("wudu-yanluobu", 110);
        set_skill("strike", 110);
        set_skill("tianchan-zhang", 110);
        set_skill("claw", 110);
        set_skill("wusheng-zhao", 110);
        set_skill("parry", 120);
        set_skill("whip", 120);
        set_skill("xiewei-bian", 120);
        set_skill("literate", 60);
        set_skill("poison", 120);
        set_skill("wudu-qishu", 120 );
        set_skill("martial-cognize", 100);

        map_skill("force", "wudu-shengong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("claw", "wusheng-zhao");
        map_skill("parry", "xiewei-bian");
        map_skill("whip", "xiewei-bian");
        map_skill("poison", "wudu-qishu");

        prepare_skill("strike", "tianchan-zhang");
        prepare_skill("claw", "wusheng-zhao");

        create_family("五毒教", 12, "護法");

        setup();

        carry_object("/d/shaolin/obj/changbian")->wield();
        carry_object("/d/city/obj/cloth")->wear();

        add_money("silver", 20);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-5000 )
        {
                command("say 做我五毒教弟子必須心狠手辣。");
                return;
        }
        if ((int)ob->query_skill("wudu-shengong", 1) < 40)
        {
                command("say 你的五毒心法還學的不夠啊。");
                return;
        }
        if ((int)ob->query_skill("wudu-qishu", 1) < 30)
        {
                command("say 我五毒教弟子以毒殺人，修習毒技是首要的。");
                command("say 你是否還應該多多鑽研本門的絕學？");
                return;
        }

       command("nod");
       command("say 不錯，不錯。");
       command("recruit "+query("id", ob));
       return;
}
