// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("�Թ���", ({"zhao gouer", "zhao", "gouer"}));
        set("title", "ؤ��һ������");
        set("gender", "����");
        set("age", 16);
        set("long",
                "�����������ŵ�С��ؤ����������·�߻������ش��˯��\n");
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 18);
        set("int", 20);
        set("con", 20);
        set("dex", 23);
        set("max_qi", 120);
        set("max_jing", 120);
        set("neili", 150);
        set("max_neili", 150);
        set("jiali", 5);
        set("combat_exp", 2500);

        set_skill("force", 30);
        set_skill("huntian-qigong", 30);
        set_skill("dodge", 30);
        set_skill("feiyan-zoubi", 30);
        set_skill("hand", 30);
        set_skill("shexing-diaoshou", 30);
        set_skill("unarmed", 30);
           set_skill("cuff", 30);
        set_skill("changquan", 30);
        set_skill("strike", 30);
        set_skill("xiaoyaoyou", 30);
        set_skill("parry", 30);
        set_skill("staff", 30);
        set_skill("fengmo-zhang", 30);
        set_skill("blade", 30);
        set_skill("liuhe-dao", 30);
        set_skill("begging", 30);
        set_skill("checking", 20);
        set_skill("literate", 10);
        set_skill("martial-cognize", 10);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "changquan");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("ؤ��", 20, "����");
        set("master_ob",1);
        setup();

        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }
        command("nod");
        command("say �����Ϊʦ����Ҫ���óԿ��׼�����ú�����ؤ����ӣ�");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}
