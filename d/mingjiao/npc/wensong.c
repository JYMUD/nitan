// WenSong.c
// pal 1997.05.11

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();

void create()
{
        set_name("�Ų���", ({ "wen cangsong", "wen", "cangsong", }));
        set("long",
        "����һλ�ߴ��ΰ���������ӣ���һ���ײ����ۡ�\n"
        "���������������е���ͷ����������򲻵�֮�£�����һ���������ݵĺ��ӡ�\n"
        );

        set("title", HIG "����" HIC "��ľ��" NOR "����ʹ");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 48);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("cuff", 120);
        set_skill("strike", 120);
        set_skill("throwing", 200);
        set_skill("literate", 100);

        set_skill("shenghuo-xinfa", 120);
        set_skill("shenghuo-bu", 120);
        set_skill("shenghuo-quan", 120);
        set_skill("guangming-zhang", 120);
        set_skill("liehuo-jian", 120);
        set_skill("wuxing-jueji", 200);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");
        map_skill("throwing", "wuxing-jueji");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        create_family("����", 37, "��ľ������ʹ");
        set("inherit_title",HIG"����"NOR"��ľ�����"NOR);

        set("inquiry", ([
                "name" : "���¾������̾�ľ������ʹ�Ų��ɣ���֪�����к�ָ�̡�",
                "����" : (: ask_job :),
                "job"  : (: ask_job :),
                "����" : (: ask_abandon :),
                "abandon" : (: ask_abandon :),
        ]));

        setup();

        carry_object("/d/mingjiao/obj/qimeigun")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object ling,axe,shugan;

    if( !(fam=query("family", this_player())) || fam["family_name"] != "����" )
        return "��λ"+RANK_D->query_respect(player)+"�����ҽ̵��֣��Ǹ������Ǹҷ��ɸ���ʲô�����ء�\n";

        if( query("combat_exp", player)>400000 )
                 return "��λ"+RANK_D->query_respect(player)+"ʵս�����Ѿ��ĸߣ�����ͷ���ܡ�\n";
        if (fam["generation"] <37)
                 return "��λ"+RANK_D->query_respect(player)+"�������̵�λ�ĸߣ�����ͷ���ܡ�\n";

        if( query("mingjiao/job", player) == "mu_kanshu" && shugan=present("shugan",player) )
        {
                if( query("owner", shugan) == query("id", player) )
                {
                        command("pat"+query("id", player));
                        if (axe=present("axe",player))
                                destruct(axe);
                        message_vision("�Ų��ɽ���һ�����ڣ���$N�����ɽ��˹�ȥ��\n",player);
                        destruct(shugan);
                        delete_temp("apply/short", player);
                        remove_call_out("reward");
                        call_out("reward",1,this_player(),"����");
               return query("name", player)+"�ɵò�����ȥ�ú���Ϣ��Ϣ��\n"; 
                }
                else
                        return "��������㿳�İɡ���͵����\n";
        }

        if( query("mingjiao/job", player) )
                return judge_jobmsg(player,0);

        command("nod"+query("id", player));

        set("mingjiao/job", "mu_kanshu", player);

        axe=new(OBJ_PATH"/axe");
        axe->move(player);
        tell_object(player,"�Ų��ɸ���һ�Ѹ�ͷ��\n");

        return "���������ã��ֵ��������󷨣���ľ�����ˣ���ȥ�����￳Щ���ɿ�������\n";

}

#include "zhangqishi.h"
