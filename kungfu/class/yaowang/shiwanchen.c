#include <ansi.h>
#include "yaowang.h"

#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;


void create()
{
        set_name("ʯ����", ({ "shi wanchen", "shi", "wanchen" }));
        set("nickname", HIR "��������" NOR);
        set("long",@LONG
����һλ�������ص����ߣ�˫Ŀʧ���������Ǻų�
���������ɡ���ʯ���������κ�����������ÿһ��
���������·硣�����һ�ζ���֮�ʣ�ʯ��������
�����ϳ��ݡ�ѬϹ��˫Ŀ���������Ұ��ɽ������
Ұ��ɽ�л�����ʮ�깦�򣬲�������ˡ��ϳ��ݡ�
�Ķ��ԣ����������˸��඾ҩ��
LONG );
        set("title", HIG "ҩ��������" NOR);
        set("gender", "����");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 60000);
        set("max_jing", 50000);
        set("neili", 60000);
        set("max_neili", 60000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 350);
        set_skill("yaogu-xinfa", 350);
        set_skill("shennong-xinjing", 350);
        set_skill("dodge", 350);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 300);
        set_skill("shennong-zhang", 300);
        set_skill("throwing", 300);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 300);
        set_skill("literate", 280);
        set_skill("poison", 600);
        set_skill("dispel-poison", 600 );
        set_skill("yaowang-shenxin", 600 );
        set_skill("medical", 400);
        set_skill("yaowang-miaoshu", 400 );
        set_skill("baicao-jue", 500 );
        set_skill("bencao-changshi", 500);
        set_skill("hunting", 300);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("ҩ����", 1, "����");
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
                "���Ǻ���" : "���Ǻ��������µ�һ������ҩ���Σ�����˵�������ĸ�СѾͷ�����е�취��",
                "�̲϶���" : "�̲϶��������˵�����ƶ�֮һ����ҩ���Σ�",
                "���˷�"   : "�Ǻǣ��������ͺ�һ�����䣬�����õ��ҵĶ��ݺ��ġ�",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
        
        if( query("character", ob) == "��������" )
        {
                command("say ���Ը��ʺ�ѧ�����Ҳ������㡣");
                return;
        }
        if( query("shen", ob)>-100000 )
        {
                command("say ��ϰ�Ҷ���ҽ���������ĺ�������");
                return;
        }
        
        if( query("combat_exp", ob)<300000 )
        {
                command("say �����ھ�����ǳ����᲻��ʲô��������ȥ�����㾭��ɡ�");
                return;
        }
        if( !query_temp("yaowang_give", ob) )
        {
                command("say ���Ȱѱ��ŵġ�ҩ����ƪ����������!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 100)
        {
                command("say �㱾�ŵ��ķ���ѧ�Ĳ�������");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 120)
        {
                command("say �����������ѧ�ʶ�ûѧ�ã�����δ��������Ķ���ҽ����");
                return;
        }

        if ((int)ob->query_skill("yaowang-miaoshu", 1) < 120)
        {
                command("say ���Ȱ�ҩ����������͸�����������Ұɡ�");
                return;
        }

        if ((int)ob->query_skill("dispel-poison", 1) < 120)
        {
                command("say ������������о�͸������");
                return;
        }

        command("pat"+query("id", ob));
        command("say ����������Ȼ��������ģ��Ϸ�����������ͽ�ܡ�");
        command("say ���������˲��ܷŹƣ����о���û��ҩ�Ķ�ҩ���Ʋ���ʹ�á��Ĺ�����������ȡ����!");
        command("say ���ǶԼ�������ֱ���ö���Խ��Խ��!");
        command("recruit "+query("id", ob));
        set("title", "���������״�����", ob);
        return;
}


int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != SHENPIAN)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
        {
                command("say ��л��λ" + RANK_D->query_respect(me) + "�����ű��ｻ���ҡ�");
                set_temp("yaowang_give", 1, me);
        }
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}

