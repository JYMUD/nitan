// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("�����", ({"kuaihuo san", "kuaihuo", "san"}));
        set("title", "ؤ���Ĵ�����");
        set("gender", "����");
        set("age", 25);
        set("long",
                "���Ǹ�����ʮ�ֽ�ʵ��������ؤ����Ц����Ķ������ƣ���֪��Ϊɶ��ô���ˡ�\n");

        set("attitude", "heroism");
        set("class", "beggar");
        set("str", 28);
        set("int", 18);
        set("con", 22);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 400);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 30);
        set("level", 6);
        set("combat_exp", 58000);

        set_skill("force", 55);
        set_skill("huntian-qigong", 55);
        set_skill("unarmed", 60);
           set_skill("cuff", 60);
        set_skill("changquan", 60);
        set_skill("dodge", 55);
        set_skill("feiyan-zoubi", 55);
        set_skill("hand", 55);
        set_skill("shexing-diaoshou", 55);
        set_skill("strike", 55);
        set_skill("xiaoyaoyou", 55);
        set_skill("parry", 55);
        set_skill("staff", 55);
        set_skill("fengmo-zhang", 55);
        set_skill("blade", 55);
        set_skill("liuhe-dao", 55);
        set_skill("begging", 55);
        set_skill("checking", 55);
        set_skill("literate", 55);
        set_skill("martial-cognize", 40);
        set_skill("stealing", 60);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "shexing-diaoshou");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("ؤ��", 20, "����");
        set("master_ob",1);
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

        if( query("gender", ob) != "����" )
                return;

        if( query("shen", ob)<0 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }
        command("nod");
        command("say �ұ�����Ϊͽ���պ�ɵ��������壬Ī����ؤ��������");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}
