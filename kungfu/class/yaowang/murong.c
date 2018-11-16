#include <ansi.h>
#include "yaowang.h"


inherit NPC;
inherit F_MASTER;
int ask_shi();
void create()
{
        set_name("Ľ�ݾ���", ({ "murong jingyue", "murong", "jingyue" }));
        set("nickname", HIC "�����" NOR);
        set("long",@LONG
ҩ���ȵڶ������Ӵ�ʦ��Ľ�ݾ�����
LONG );

        set("gender", "����");
        set("age", 33);
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

        set_skill("force", 200);
        set_skill("yaogu-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("xuefu-mizong", 200);
        set_skill("strike", 200);
        set_skill("dusha-zhang", 200);
        set_skill("hand", 200);
        set_skill("lansha-shou", 200);
        set_skill("jiuqu-zhegufa", 200);
        set_skill("parry", 200);
        set_skill("staff", 200);
        set_skill("shennong-zhang", 200);
        set_skill("throwing", 200);
        set_skill("xuwen-qixingding", 200);
        set_skill("wuxing-jueming", 200);
        set_skill("literate", 200);
        set_skill("poison", 200);
        set_skill("dispel-poison", 200 );
        set_skill("yaowang-shenxin", 200 );
        set_skill("medical", 200);
        set_skill("yaowang-miaoshu", 200 );
        set_skill("baicao-jue", 200 );
        set_skill("bencao-changshi", 200);
        set_skill("hunting", 180);

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
                "ʯ����"   : (: ask_shi :),
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<50000 )
        {
                command("say �����ھ�����ǳ����᲻��ʲô��������ȥ�����㾭��ɡ�");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 50)
        {
                command("say �㱾�ŵ��ķ���ѧ�Ĳ�������");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 100)
        {
                command("say �����������ѧ�ʶ�ûѧ�ã�����δ��������Ķ���ҽ����");
                return;
        }

        if ((int)ob->query_skill("medical", 1) < 100)
        {
                command("say ���Ȱ�ҽ������͸�����������Ұɡ�");
                return;
        }


        command("pat"+query("id", ob));
        command("say ����������Ȼ��������ģ��Ҿ����������ͽ�ܡ�");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "bonze" )
                set("class", "bonze", ob);
        return;
}

int ask_shi()
{
        object me;
        object ob;

        me = this_player();
        
        if( query("family/family_name", me) != "ҩ����" )
                return notify_fail( "�㲻������ҩ���ȵģ���������ʲô��");

        

        if( query("shen", me)<-100000 )
                return notify_fail("��������������̫�࣬ȥ����Ҳ�����㡣");


        message_vision(HIC "$N" HIC "΢΢һЦ����������ʦ����ں�ɽ"
                       "�Ķ���·���������������ң���\n" NOR,
                       this_object(), me);
        set_temp("murong_ask", 1, me);
        return 1;
}
void unconcious()
{
        die();
}

