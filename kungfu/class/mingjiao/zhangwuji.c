// This program is a part of NT MudLIB
// zhangwuji.c

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_jiuyang();
mixed ask_qiankun();
mixed ask_ling();

string ask_book();
string ask_qishang();

int ask_hu_quest();
int ask_hu();
int ask_hdg();
void destroy(object ob);
void restart(object me, object ob);

void create()
{
        seteuid(getuid());
        set_name("���޼�", ({ "zhang wuji", "zhang", "wuji" }));
        set("long", @LONG
���̽������޼ɣ�ͳ������ʮ����ڣ��������ƣ�߳��ǧ�
�������񹦡�����Ǭ����Ų�ơ��������£��ǽ����в�������
����Ӣ�ۡ�
LONG );
        set("title",HIG "����" HIM " ����" NOR);
        set("gender", "����");
        set("age", 20);
        set("no_get", 1);
        set("shen_type",1);
        set("attitude", "friendly");
        set("class", "fighter");

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("qi", 5800);
        set("max_qi", 5800);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 120);
        set("level", 50);
        set("combat_exp", 2900000);
        set("score", 455000);
        set("book_count", 1);

        set_skill("force", 600);
        set_skill("unarmed", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("cuff", 600);
        set_skill("sword", 600);
        set_skill("blade", 600);
        set_skill("strike", 600);
        set_skill("claw", 600);
        set_skill("throwing", 600);
        // set_skill("duoming-jinhua", 450);
        set_skill("jiuyang-shengong", 600);
        set_skill("shenghuo-xinfa", 600);
        set_skill("shenghuo-shengong", 600);
        set_skill("lingxu-bu", 600);
        set_skill("shenghuo-bu", 600);
        set_skill("qingfu-shenfa", 600);
        set_skill("qiankun-danuoyi", 600);
        set_skill("qishang-quan", 600);
        set_skill("taiji-quan", 600);
        set_skill("taiji-jian", 600);
        set_skill("taiji-dao", 600);
        set_skill("lieyan-dao", 600);
        set_skill("liehuo-jian", 600);
        // set_skill("yingzhua-shou", 450);
        // set_skill("hanbing-mianzhang", 450);
        set_skill("shenghuo-ling", 600);
        set_skill("guangming-zhang", 600);
        set_skill("medical", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("guangming-jing", 600);

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("strike","guangming-zhang");
        map_skill("cuff", "qishang-quan");
        map_skill("sword","shenghuo-ling");
        map_skill("parry","qiankun-danuoyi");
        map_skill("blade","taiji-dao");
        // map_skill("claw", "yingzhua-shou");
        // map_skill("throwing", "duoming-jinhua");
        // map_skill("strike", "hanbing-mianzhang");

        prepare_skill("cuff", "qishang-quan");

        set("inherit_title",HIG"����"HIY"����ʹ��"NOR);
        create_family("����", 34, "����");

        set("no_teach", ([
                "jiuyang-shengong"  : "����ҿɲ��ܴ��㡣",
                "taiji-jian"        : "�㻹������̫ʦ���ɣ�",
                "taiji-quan"        : "�㻹������̫ʦ���ɣ�",
                "taiji-dao"         : "�㻹������̫ʦ���ɣ�",
                "qishang-quan"      : "��ѧ����ȭ�㻹�������常лѷ�ɣ�",
                "qiankun-danuoyi"   : "Ǭ����Ų��ֻ�����̽��������������ѵ�������������",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.hua") :),
                (: command("perform sword.xi") :),
                (: command("perform sword.lian") :),
                (: command("perform sword.can") :),
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
                (: command("yun shield") :),
                (: command("yun powerup") :),
                (: command("yun recover") :),
        }) );

        set("chat_chance", 2);
        set("chat_msg",({
                "���޼ɷ�Ȼ˵�������ɷ��Թ�Ϊ��, ����ɳ��, ��Ԫ��ҵδ��, ͬ������Ŭ��!��\n",
                "���޼�̾��������ʧһ֪��, ����λ�, �������, ����, ��������?��\n",
                "���޼ɵ����ҽ��ֵ�����: ��������, ���˼�Ϊ��, ��������, ������ħ!��\n",
        }));

        set("inquiry",([
                "����"     : "���������������ʲô����\n",
                "��ëʨ��" : "�������常л������ְ˾��\n",
                "лѷ"     : "���������常�Ĵ�š�\n",
                "�Ŵ�ɽ"   : "�������Ҹ���������? \n",
                "������"   : "����������������΢������\n",
                "������"   : "��̫ʦ�������ɺ�? \n",
                "����"     : "����ʧһ֪��, ����λ�, �������, ����, ��������?\n",
                "С��"     : "С���ҿ�һֱ�������ĺô���\n",
                "������"   : "������ȥ����ɽ, �������ҡ�\n",
                "�����ؼ�" : (: ask_jiuyang :),
                "������"   : (: ask_ling :),
                "Ǭ����Ų��" : (: ask_qiankun :),
                "����ͨ"   : (: ask_hu_quest :),
                "����ţ"   : (: ask_hu :),
                "������"   : (: ask_hdg :),
                "����ȭ��" : (: ask_qishang :),
                "�ؼ�"     : (: ask_book :),

        ]));
        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);

        set("master_ob",5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/book/shenghuo-ling")->wield();
        add_money("silver",70);
}

void init()
{
        object ob;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }
        if( interactive(ob=this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1,ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob)!=environment()) return;
        if( query("shen", ob)<-50000 )
        {
                command("wield yitian jian");
                command("hit"+query("id", ob));
                command("unwield yitian jian");
        } else
        if( query("shen", ob)<-5000 )
        {
                command("say ħ����������ѧ������������Ȱ������������"
                        "���سɷ�");
        } else
        if( query("shen", ob)<-100 )
        {
                command("say ��λ���ѣ����н��������е����������߽�аħ�����");
        } else
        if( query("shen", ob) >= 0 )
        {
                command("say �������������ߣ�Ȱ����ӱ��ء�");
        } else
        if( query("shen", ob)>50000 )
        {
                command("say �������ϣ����޼�һ�񣬴������ձ�Ϊ�����̳���");
        }
        return;
}

int accept_fight(object ob)
{
        if( query("combat_exp", ob)<30000 && query("shen", ob)>0 )
        {
                message_vision("�������������ǿ���ݣ��㲻���ҵĶ��֣�"
                               "��ȥ�ɡ�\n",ob);
                return 0;
        }
        message_vision("���޼�һ����˵������λ" + RANK_D->query_respect(ob) +
                       "����������ˡ�\n", ob);
        return 1;
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam = query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "����" )
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if ( ob_fam["generation"] > my_fam["generation"] + 2)
        {
                command("say " + RANK_D->query_respect(ob) + "������ȥ�ҽ��������ֵܺú�ѧѧ�书�ɡ�");
                return;
        }

        if( query("shen", ob)<90000 )
        {
                command("say ����������������û�������������ذɡ�");
                return;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                command("say ��ľ���̫�٣��ú���ȥ���������������ɱ�������̶����� !");
                return;
        }

        command("say �����ã�������������һλ�������֣����ǿ�ϲ�ɺ� !");

        command("say ��ϲ������Ϊ���̹���ʹ�ߣ�");
        command("recruit "+query("id", ob));

        return;
}

int accept_object(object who, object ob)
{
        int r;
        object me;
        mapping fam;

        me = this_object();
        fam=query("family", who);

        if (playerp(ob))
                return 0;

        if (r = ::accept_object(who, ob))
                return r;

          if( query("id", ob) == "jin mao" )
        {
                tell_object(who, GRN "���޼ɼ�����˵�������ҵ��ҵ��常�ˡ�\n" NOR);
                if( !query_temp("marks/�常", who) )
                        set_temp("marks/�常", 1, who);
                remove_call_out("destrory");
                call_out("destrory", 1, ob);
                return 1;
        }
          if( query("id", ob) == "shenghuo ling" )
        {
                if (! (fam) || fam["family_name"] != "����")
                {
                        command("thank"+query("id", who));
                        command("say ��л��Ϊ�����һ���ʥ���֪��Ӧ����ôлл�㣿\n");
                        call_out("destroy", 1, ob);
                        return 1;
                }
                if (fam["family_name"] == "����"
                     && (fam["master_name"] != "���޼�" || query_temp("mj_jiaozhu", who)) )
                {
                        command("nod"+query("id", who));
                        command("say ��Ϊ�����һ���ʥ���ʹ��Ͳ�С����\n");
                        call_out("destroy", 1, ob);
                        addn("shen", 2000, who);
                        addn("combat_exp", 100+random(50), who);
                        tell_object(who,HIW"�㱻������һЩ����;���ֵ��\n"NOR);
                        return 1;
                }
                if( query("mj_jiaozhu", me) )
                {
                        command("pat"+query("id", who));
                        command("say �������������Ѿ��������ҵ��ˡ�\n");
                        return 0;
                }
                command("ah"+query("id", who));
                command("say �㾹�һ��˱���ʥ��������ҵĵ��ӣ�");
                command("say �ϴ���������������Ѱ��ʥ���ߵ�����ϰ�����񹦣���ȥ�ص������԰ɡ�");
                set_temp("mj_jiaozhu", 1, who);
                set("mj_jiaozhu", 1, me);
                call_out("destroy", 1,  ob);
                remove_call_out("restart");
                call_out("restart", 3600, me, ob);
                return 1;
        } else
                return 0;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "�һ�������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liehuo-jian/jue",
                           "name"    : "�һ�������",
                           "sk1"     : "liehuo-jian",
                           "lv1"     : 100,
                           "neili"   : 1000,
                           "gongxian": 400,
                           "shen"    : 50000, ]));
                break;

        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/xi",
                           "name"    : "������",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/lian",
                           "name"    : "������",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;
        case "�⻪��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/hua",
                           "name"    : "�⻪��",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2400,
                           "gongxian": 900,
                           "shen"    : 80000, ]));
                break;
        case "��Ѫ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/can",
                           "name"    : "��Ѫ��",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "���ػ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/jiu",
                           "name"    : "���ػ���",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "����һ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/hun",
                           "name"    : "����һ��",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/pi",
                           "name"    : "��������",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/po",
                           "name"    : "��������",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "ħ�����޼�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/ri",
                           "name"    : "ħ�����޼�",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_learn/jiuyang-shengong/enable_weapon",
                           "name"    : "��������",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "��Ų��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/yi",
                           "name"    : "��Ų��",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 200,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "ŲתǬ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/nuozhuan",
                           "name"    : "ŲתǬ��",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 1000,
                           "neili"   : 5000,
                           "force"   : 1000,
                           "gongxian": 3000,
                           "reborn"  : 1,
                           "shen"    : 100000, ]));
                break;
        default:
                return 0;
        }
}

mixed ask_jiuyang()
{
        mapping fam;
        object ob;
        object me = this_player();

        if( !(fam=query("family", this_player())) || fam["family_name"] != "����" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";

        if( !query_temp("marks/�常", this_player()) )
                return "������ܰ����ҵ��ҵ��常лѷ���ǻ����Կ��ǣ�";

        if( query("jiuyang/zhang", me) )
                return "��֪�����������С��˻��ĺ�����ô��";

        set("jiuyang/zhang", 1, me);
        return "�뵱��̫ʦ�������������������ɡ�������ʥ�����������������˵���������С���\n"+
               "��֪���˻��кκ��塣";
}

/*
mixed ask_ling()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "����")
                return RANK_D->query_respect(this_player()) +
                       "�뱾������������Ҫ����Ǻξ��ģ�\n";

        if (this_player()->query_skill("shenghuo-ling", 1) < 100)
                return "���ʥ�������̫ǳ��ҪȥҲû�õģ�\n";

        if (this_player()->query_skill("qiankun-danuoyi", 1) < 100)
                return "���Ǭ����Ų���ķ�����̫ǳ��ʥ��������ҿɲ�̫���ģ�\n";

   ob = new("/d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$NҪ��һ�������\n",this_player());

        return "�ðɣ�ƾ�������������������������ս��";
}
*/
mixed ask_ling()
{
        mapping family, skl;
        string *sname;
        object ob;
        int i;

        if( !(family=query("family", this_player())) || family["family_name"] != "����" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";

        skl = this_player()->query_skills();
        sname  = sort_array( keys(skl), (: strcmp :) );

        for(i=0; i<sizeof(skl); i++)
        {
                if (skl[sname[i]] < 30)
                return RANK_D->query_respect(this_player()) +
                "����������������ȡ�����";
        }

        ob = new("d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$NҪ��һ�������\n",this_player());

        return "�ðɣ�ƾ�������������������������ս��";

}

mixed ask_qiankun()
{
        object obj,me;
        me = this_player();

        if (this_player()->query_skill("shenghuo-shengong", 1)<100)
        {
                command("say " + RANK_D->query_respect(me) + "�ƺ�ʥ������Ϊ��������");
                return 1;
        }
        if( query("combat_exp", this_player())<800000 )
        {
                command("say " + RANK_D->query_respect(me) + "�ƺ�ʵս���黹������");
                return 1;
        }
        if (this_player()->query_skill("force", 1) < 100)
        {
                command("say " + RANK_D->query_respect(me) + "�ƺ������ڹ���Ϊ��������");
                return 1;
        }
              if( query_temp("marks/Ų��", this_player()) )
              {
                command("say �㲻�Ǹող��ʹ���");
                return 1;
        }
        else
        {
                command("say �ðɣ��Ҿ�׼���������������Ǭ����Ų�ơ��Ժ���Ҫ���������̡�");
                // command("say �㵽����ǰ������ȥ��˵����׼��ġ�");
                command("pat"+query("id", me));
                command("addoil"+query("id", me));
                set_temp("marks/Ų��", 1, this_player());
                return 1;
        }

}

int ask_hu_quest()
{
        object me = this_player();
        if( query_temp("hu/quest1", me) != 2 )
        {
                command("say ��ôͻȻ��������ʲô��");
                return 1;
        } else
        {
                command("say ԭ�������������ڣ�");
                command("jump");
                command("say �Ұ�������ݺݵ���������һ�һ�٣�������Ҳ�Լ������Լ��Ķ����ˡ�");
                command("say ���������������Կ�������ػ�ܸ��ˡ�");
                set_temp("hu/quest1", 3, me);
                return 1;
        }
}

int ask_hu()
{
        object me = this_player();

        if( !query_temp("hu/quest2", me) )
        {
                command("say ����ţ�����ųƵ���ҽ�ɣ�ҽ��һ��������Ƣ���е�֡�");
                return 1;
        } else
        {
                command("ah");
                command("say ���ǶԲ�ס��������̽�Ҫ���£���ʵ�ڳ鲻����");
                command("say �鷳�����������˰�æ�������Ϳ��š�");
                command("say ����������޼ɰ��ã���������С�����ӡ�");
                command("say �������������ȥ���ú����������ɡ�");
                me->apply_condition("hu_quest", 5);
                new("/d/mingjiao/obj/tieyan")->move(me);
                return 1;
        }
}

int ask_hdg()
{
        object me = this_player();
        command("say �������Ǻ���ţ��ҽ�ľ�����");
        command("say ���ڳ����ϰ����������ź��������ҵ��ˡ�");
        set_temp("hdg", 1, me);
        return 1;
}

string ask_qishang()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "����" || fam["master_name"] != "���޼�")
                return "��....���ҿɲ��������������ʱ��˰ɡ�";

        if( query("can_perform/xiexun/qishang", me) )
                return "�ף��常�����Ѿ�������ȭ��ȭ���������\n";

        if( query_temp("marks/����", me) )
                return "�ף��Ҳ��ǽ������ȥ�ݷ����常лʨ������\n";

        // me->set("luopan/bhd");
        set_temp("marks/����", 1, me);

        command("hmm");
        command("whisper"+query("id", me)+"���常�ڼ��������ϣ����λ�ڻƵ����Ա��Ű���ʮ���Զ����ٸ�����ĵط���");
        // new("/d/mingjiao/obj/luopan")->move(this_object());
        // command("give luo pan to " + me->query("id"));
        return "������ȭ���ǵ������常���Դ��ҵľ�����������������ĺ��������ͳ���ȥ�ݷ����常�ɣ�\n";
}

string ask_book()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "����" || fam["master_name"] != "���޼�")
                return "����һ��̫��ȭ�����ǵ������䵱��̫ʦ���͸��ҵġ�";

        set_temp("marks/��1", 1, me);
        return "����һ��̫��ȭ�����ǵ������䵱��̫ʦ���͸��ҵģ����ҽ���ɢ���ˡ�";
}

void destroy(object ob)
{
        if (ob) destruct(ob);
}

void restart(object me, object ob)
{
        if( query("mj_jiaozhu", me) )
                delete("mj_jiaozhu", me);

        if (ob) destruct(ob);
}

/*
void unconcious()
{
        die();
}
*/
