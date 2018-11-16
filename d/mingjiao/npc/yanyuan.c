// YanYuan.c
// pal 1997.05.11

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();

void create()
{
        set_name("��ԫ", ({ "yan yuan", "yan", "yuan", }));
        set("long",
        "����һ���������ֵĺ��ӣ���һ���ײ����ۡ�\n"
        "���������������е���ͷ����������򲻵�֮�£�����һ���������ݵĺ��ӡ�\n"
        );
        set("title", HIG "����" HIY "������" NOR "����ʹ");

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

        set("inquiry", ([
                "name" : "���¾������̺���������ʹ��ԫ����֪�����к�ָ�̡�",
                "����" : (: ask_job :),
                "job"  : (: ask_job :),
                "����" : (: ask_abandon :),
                "abandon" : (: ask_abandon :),
        ]));

        create_family("����", 37, "����������ʹ");
        set("inherit_title",HIG"����"NOR"���������"NOR);

        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object qiao;

    if( !(fam=query("family", this_player())) || fam["family_name"] != "����" )
        return "��λ"+RANK_D->query_respect(player)+"�����ҽ̵��֣��Ǹ������Ǹҷ��ɸ���ʲô�����ء�\n";

        if( query("combat_exp", player)>400000 )
                 return "��λ"+RANK_D->query_respect(player)+"ʵս�����Ѿ��ĸߣ�����ͷ���ܡ�\n";

        if (fam["generation"] <= 37)
                 return "��λ"+RANK_D->query_respect(player)+"�������̵�λ�Ѿ��ĸߣ�����ͷ���ܡ�\n";

        if( query("mingjiao/job", player) == "tu_didao" && query_temp("didao_done", player) )
        {
                command("haha"+query("id", player));
                if (qiao=present("tie qiao",player))
                        destruct(qiao);
                command("say ���ǵĵص�����ǰ����һ����");
                delete_temp("didao_done", player);
                remove_call_out("reward");
                call_out("reward",1,this_player(),"�ڵص�");
               return query("name", player)+"�ɵò�����ȥ�ú���Ϣ��Ϣ��\n"; 
        }

        if( query("mingjiao/job", player) )
                return judge_jobmsg(player,0);

        command("nod"+query("id", player));

        set("mingjiao/job", "tu_didao", player);

        qiao=new(OBJ_PATH"/qiao");
        qiao->move(player);
        tell_object(player,"��ԫ����һ�����¡�\n");

        return "���Ǻ����츺���ڵص����������д��ó�����ȥ��������һ�𽫵ص�����㡣\n";

}

#include "zhangqishi.h"
