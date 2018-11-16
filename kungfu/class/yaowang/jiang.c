#include <ansi.h>
#include "yaowang.h"


inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("����ɽ", ({ "jiang tieshan", "jiang", "tieshan" }));
        set("nickname", HIC "������" NOR);
        set("long",@LONG
ҩ���ȵڶ������ӽ���ɽ��
LONG );

        set("gender", "����");
        set("age", 30);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 180);
        set_skill("yaogu-xinfa", 180);
        set_skill("dodge", 180);
        set_skill("xuefu-mizong", 180);
        set_skill("strike", 180);
        set_skill("dusha-zhang", 180);
        set_skill("hand", 180);
        set_skill("lansha-shou", 180);
        set_skill("jiuqu-zhegufa", 180);
        set_skill("parry", 180);
        set_skill("staff", 180);
        set_skill("shennong-zhang", 180);
        set_skill("throwing", 180);
        set_skill("xuwen-qixingding", 180);
        set_skill("wuxing-jueming", 180);
        set_skill("literate", 160);
        set_skill("poison", 160);
        set_skill("dispel-poison", 160 );
        set_skill("yaowang-shenxin", 160 );
        set_skill("medical", 160);
        set_skill("yaowang-miaoshu", 160 );
        set_skill("baicao-jue", 160 );
        set_skill("bencao-changshi", 160);
        set_skill("hunting", 160);

        map_skill("force", "yaogu-xinfa");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("ҩ����", 2, "����");
        set("class", "bonze");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.tengshe" :),
                (: perform_action, "whip.panying" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suolong" :),
                (: perform_action, "claw.lianhuan" :),
                (: perform_action, "strike.duchan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        set("inquiry", ([
                "���Ǻ���" : "���Ǻ��������µ�һ������ҩ���Σ�",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<20000 )
        {
                command("say �����ھ�����ǳ����᲻��ʲô��������ȥ�����㾭��ɡ�");
                return;
        }

        if ((int)ob->query_skill("medical", 1) < 20)
        {
                command("say ����ȥС���Ƕ�ѧЩ����ҽ���ɡ�");
                return;
        }


        command("pat"+query("id", ob));
        command("say ����������Ȼ��������ģ��Ҿ����������ͽ�ܡ�");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "bonze" )
                set("class", "bonze", ob);
        return;
}


void unconcious()
{
        die();
}

