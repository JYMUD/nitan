// This program is a part of NITAN MudLIB
// gao-laozhe.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

void create()
{
        set_name("������", ({ "gao laozhe", "gao" }));
        set("title", HIR"��ɽ��ʮ��������"NOR);
        set("long",
"�����ǻ�ɽ�ĳ��ϸ����ߡ�һ���벻�ں���ģ�����������죬���²��ӻ���\n"
"������׷������ʦ�ְ����ߡ�\n");
        set("gender", "����");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 25);
        set("con", 28);
        set("dex", 25);
        set("qi", 4200);
        set("max_qi", 4200);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 60);
        set("level", 30);
        set("combat_exp", 1750000);
        set("score", 60000);

        set_skill("cuff", 600);
        set_skill("force", 600);
        set_skill("blade", 600);
        set_skill("sword", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("strike", 600);
        set_skill("huashan-neigong", 600);
        set_skill("zixia-shengong", 600);
        set_skill("huashan-shenfa", 600);
        set_skill("huashan-quan", 600);
        set_skill("huashan-zhang", 600);
        set_skill("poyu-quan", 600);
        set_skill("fanliangyi-dao", 600);
        set_skill("huashan-sword", 600);
        set_skill("hunyuan-zhang", 600);
        set_skill("feiyan-huixiang", 600);
        set_skill("literate", 600);
        set_skill("jianyi", 600);
        set_skill("martial-cognize", 600);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "fanliangyi-dao");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "huashan-jian");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        create_family("��ɽ��", 12, "����");

        set("inquiry", ([
                "��ϼ��" : "���Ǳ������ϵ��ڹ��ķ�����˵��ϼ�и������ܣ���ϧ��ʧ�������ˡ�\n",
                "����"     : "���˵�˵�Щ���᣿\n",
        ]));

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "blade.sanshen" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string ob_fam;

        ob_fam=query("family/family_name", ob);
        if (! permit_recruit(ob))
                return;

        if (ob_fam == "��ɽ��" && ob->query_skill("zixia-shengong", 1) < 100)
        {
                command("say �ҿ������ϼ�񹦻�ûѧ���Ұɣ������б���"
                        "��ϼ�ؼ���������ж���");
                return;
        }

        if ((int)ob->query_skill("sword", 1) < 100)
        {
                command("say ��Ľ�����ûѧ���ң����ȥ���û���������");
                return;
        }

        if (ob_fam == "��ɽ��" && (int)ob->query_skill("huashan-sword", 1) < 100 ||
            ob_fam == "��ɽ����" && (int)ob->query_skill("kuangfeng-jian", 1) < 100)
        {
                command("say ��ɽ�����Ϳ�罣���Ǳ��ɵ��ӱ��뾫ͨ���似��������"
                        "���Ž�����");
                return;
        }

        if( query("shen", ob)<10000 )
        {
                command("say �һ�ɽ�����������������ɣ��Ե���Ҫ��"
                        "�ϣ��㻹�ö���Щ����������£�");
                return;
        }

        if (ob_fam == "��ɽ����")
        {
                command("say �㰡��... ����Ҳ���ǽ���֮�����ܺ��ߣ����ˣ�����Ҳ�ա�");
                delete("family", ob);
        }

        command("say �ðɣ��Ҿ��������ˣ�������ǻ�ɽ�ɻ�Ҫ��������Щ��������");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "fighter" )
                set("class", "fighter", ob);
}

#include "zhanglao.h"
