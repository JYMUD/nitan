// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("�����", ({"yu hongxing", "yu", "hongxing"}));
        set("title", "ؤ��˴�����");
        set("gender", "����");
        set("age", 30);
        set("long",
                "����λЦ���е�ؤ��˴����ӣ����Զ��ǣ����С���á�\n");
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 20);
        set("int", 30);
        set("con", 22);
        set("dex", 20);
        set("max_qi", 920);
        set("max_jing", 630);
        set("neili", 1120);
        set("max_neili", 1120);
        set("jiali", 90);
        set("level", 11);
        set("combat_exp", 300000);

        set_skill("force", 98);
        set_skill("huntian-qigong", 96);
        set_skill("unarmed", 100);
           set_skill("cuff", 100);
        set_skill("changquan", 100);
        set_skill("hand", 98);
        set_skill("shexing-diaoshou", 80);
        set_skill("dodge", 100);
        set_skill("feiyan-zoubi", 100);
        set_skill("strike", 102);
        set_skill("xiaoyaoyou", 102);
        set_skill("staff", 90);
        set_skill("fengmo-zhang", 90);
        set_skill("blade", 100);
        set_skill("liuhe-dao", 100);
        set_skill("parry", 101);
        set_skill("begging", 100);
        set_skill("stealing", 90);
        set_skill("checking", 90);
        set_skill("training", 90);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("blade","liuhe-dao");
        map_skill("parry","liuhe-dao");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "changquan");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("ؤ��", 19, "����");

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",3);
        setup();

        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("int", ob)<25 )
                return;

        if( query("shen", ob)<0 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }
        command("say �����������Ϊ����ֻ���߹������˼Һ��Ҳ��ر���Щ����ͽ����");
        command("say ��Ҷ�ҪΪ��Զ���밡��");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}
