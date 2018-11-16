// chen.c �½���

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "yunlong.h"
int ask_tuihui();
mixed ask_me();
string ask_me1();

void create()
{
        set_name("�½���", ({ "chen jinnan", "chen","jinnan" }));
        set("title", HIR "��ػ�"HIM"�ܶ���"NOR );
        set("nickname", HIC "Ӣ���޵�" NOR);
        set("long",
                "\n����һ����ʿ����������������ɫ�Ͱ���\n"
                "������������������ػ��ܶ����½��ϣ�\n"
                "��˵ʮ�˰����գ�������ͨ��\n"
                "ż������߿��������پ���Ŀ����磬Ӣ�����ˡ�\n");
        set("gender", "����");
        set("class", "scholar");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 120);
        set("combat_exp", 2000000);
        set("score", 500000);
        set_skill("literate", 600);

        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("parry", 600);
        set_skill("claw", 600);
        set_skill("blade", 600);
        set_skill("wuhu-duanmendao", 600);
        set_skill("sword", 600);
        set_skill("yunlong-jian", 600);
        set_skill("whip", 600);
        set_skill("yunlong-bian", 600);
        set_skill("houquan", 600);
        set_skill("yunlong-xinfa", 600);
        set_skill("yunlong-shengong", 600);
        set_skill("yunlong-shenfa", 600);
        set_skill("ningxue-shenzhao", 600);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("unarmed", "houquan");
        map_skill("parry", "ningxue-shenzhao");
        map_skill("claw", "ningxue-shenzhao");

        prepare_skill("claw","ningxue-shenzhao");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "claw.ji" :),
                (: exert_function, "recover" :),
        }) );

        create_family("������",1, "��ɽ��ʦ");
        set("book_count", 1);
        set("inquiry", ([
                "��ػ�" :  "ֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��",
                "���" :  "�����������ػ�һͬ���帴����",
                "���帴��" : "ȥ�ײĵ�ͻش�����ϸ���ưɣ�\n",
                "����"     : "�����£�\n",
                "�п�"     : "�����£�\n",
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "��Ѫ��צ" : (: ask_me :),
                "��������" : (: ask_me1 :),
                "�˻�" : (: ask_tuihui :),
                "tuihui"   : (: ask_tuihui :),
        ]) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_join","join");
}

int ask_tuihui()
{
        object ob;
        ob=this_player();

        if( query("party/party_name", ob) != "��ػ�" )
        {
                message_vision("�½���Ц��Ц����$N˵�����㻹û"
                               "��������ػ��أ���ʲô�ˣ�\n", ob);
                return 1;
        }
        command("look "+query("id", ob));
        command("sigh ");
        command("say ���帴������Ҫ����־ʿ����ȥ��! ");
        delete("party", ob);
        delete("rank", ob);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/ningxue-shenzhao/ji", me) )
                return "����Ὺ��Ц�����˻������ҡ�";

/*
        if( !query("story/shenzhao", me) )
                return "�����������";
*/

        if( query("shen", me)<1000000 )
                return "ϰ��֮������һ���������֣����巽���㻹���ò�����";

        if (me->query_skill("ningxue-shenzhao", 1) < 250)
                return "�����Ѫ��צ�������ң�Ҫ��������";

        message_vision(HIY "$n" HIY "���˵�ͷ������Ϊצ��"
                       "�������������˫צ��ʱ�ó�����צӰ��"
                       "���ƻֺ��ޱȡ�\n" NOR,
                       me, this_object());
        command("nod");
        command("say ��������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ����硹��һ�С�\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 500000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 500000);
        if (me->can_improve_skill("ningxue-shenzhao"))
                me->improve_skill("ningxue-shenzhao", 500000);
        set("can_perform/ningxue-shenzhao/ji", 1, me);
        return 1;
}

string ask_me1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count") < 1)
                return "�������ˣ����ɵ������澭���ڴ˴���";
        addn("book_count", -1);
        ob = new("/clone/book/yljianpu");
        ob->move(this_player());
        return "�ðɣ��Ȿ���������ס����û�ȥ�ú����С�";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yunlong-shengong", 1) < 50)
        {
                command("say �����������ڼ��书���������ڹ��ķ���");
                command("say " + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�����������϶��µ㹦��");
                return;
        }
        if( query("weiwang", ob)<60 )
        {
                command("say ���������书�����޵У��������ţ�\n�ش����������������壬Ϊ���²���ı������\n");
                command("say " + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ���ȳ�ȥ��һ�������������춯�صĴ��£�");
                return ;
        }
        if( query("shen", ob)>0 && query("shen", ob)<5000){
                command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return ;
        }
        if( query("weiwang", ob)<80 )
        {
                if( query("shen", ob)<0 )
                command("say "+ RANK_D->query_respect(ob) +"��Ȼ��а�����ˣ���Ҳ������Щ���¡�\n");
                command("chat ����ػ�������Ϊ����һ����ǰ����δ��֮�¡�\n");
                command("chat ���¿������ң��������ţ������Ȼ���ֺ����ۣ�\n");
                command("chat �����������ɣ���\n");
                command("chat �벻����һ������ҵ�������������˴��ˣ�����������������\n");
                message_vision(HIC "$N�Ľ�����������ˣ�\n" NOR,this_player());
                set("weiwang", 80, ob);
        }
        command("recruit "+query("id", ob));
        if( (!query("class", ob)) || (query("class", ob) != "fighter") )
                set("class", "fighter", ob);
}

#include "/kungfu/class/yunlong/tiandihui.h"
