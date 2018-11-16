// zhaixing.c ժ����

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include "xingxiu.h"
#include <ansi.h>

string ask_me();
string ask_book();
string ask_job();

void create()
{
        set_name("ժ����", ({ "zhaixing zi", "zhaixing", "zi" }));
        set("nickname", HIR "�����ɴ�ʦ��" NOR);
        set("long",
                "�����Ƕ�����Ĵ���ӡ������ɴ�ʦ��ժ���ӡ�\n"
                "����ʮ���꣬�����������۹���͸��һ˿����֮����\n");
        set("gender", "����");
        set("age", 35);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 26);
        set("int", 28);
        set("con", 26);
        set("dex", 26);

        set("max_qi", 3400);
        set("max_jing", 1800);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 80);
        set("combat_exp", 420000);
        set("shen_type", -1);

        set_skill("force", 140);
        set_skill("huagong-dafa", 140);
        set_skill("guixi-gong", 140);
        set_skill("throwing", 120);
        set_skill("feixing-shu", 120);
        set_skill("dodge", 120);
        set_skill("zhaixing-gong", 120);
        set_skill("whip", 120);
        set_skill("chanhun-suo", 120);
        set_skill("strike", 120);
        set_skill("chousui-zhang", 120);
        set_skill("claw", 120);
        set_skill("sanyin-zhua", 120);
        set_skill("parry", 120);
        set_skill("poison", 140);
        set_skill("medical", 120);
        set_skill("xingxiu-qishu", 140);
        set_skill("literate", 140);

        set("no_teach", ([
                "huagong-dafa" : "������Ҫ�������Դ��ڡ�",
        ]));

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("parry", "chousui-zhang");
        map_skill("throwing", "feixing-shu");
        map_skill("whip", "chanhun-suo");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        set("coagents", ({
                ([ "startroom" : "/d/xingxiu/riyuedong",
                   "id"        : "ding chunqiu", ]),
        }));

        set("inquiry", ([
                "���ĵ�"    : (: ask_me :),
                "�ؼ�"      : (: ask_book :),
                "��ɽ����"  : (: ask_book :),
                "job"       : (: ask_job :),
        ]));
        set("dan_count", 1);
        set("book_count", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.zhua" :),
                (: perform_action, "strike.tao" :),
                (: perform_action, "strike.shi" :),
                (: perform_action, "strike.dan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);

        create_family("������", 2, "����");

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/lianzi")->wield();
}

void attempt_apprentice(object ob)
{
        if( query("shen", ob)>0 )
        {
             command("heng");
             command("say ����������������Щ�������ˣ��㻹�ǻ�ȥ�ɣ�");
             return;
        }
        command("say �ðɣ��Ҿ��������ˡ�");
        welcome(ob);
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (query("dan_count") < 1)
                return "�������ˣ�û�����ĵ��ˡ�\n";

        addn("dan_count", -1);
        ob = new("/d/xingxiu/obj/lianxindan");
        ob->move(this_player());
        return "��Щ���ĵ������õ��˰ɡ�\n";
}

string ask_book()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (query("book_count") < 1)
                return "�������ˣ�����ûʲôʣ���ˡ�\n";

        addn("book_count", -1);
        ob = new("/clone/book/throw_book");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����û�ȥ�úÿ����ɡ�\n";
}

int accept_ask(object me, string topic)
{
        switch(topic)
        {
             case "����" :
             case "����" :
             case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

             case "��������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/tianshan-zhang/fugu",
                                 "name"     :  "��������",
                                 "sk1"      :  "tianshan-zhang",
                                 "lv1"      :  60,
                                 "shen"     :  -2200,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "��ѩ�׷�":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/tianshan-zhang/xue",
                                 "name"     :  "��ѩ�׷�",
                                 "sk1"      :  "tianshan-zhang",
                                 "lv1"      :  60,
                                 "shen"     :  -22000,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "���컨��":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/feixing-shu/hua",
                                 "name"     :  "���컨��",
                                 "sk1"      :  "feixing-shu",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "shen"     :  -5500,
                                 "family/gongji" :  400 ]));
                  break;

             case "��ǽ":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huo",
                                 "name"     :  "��ǽ",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  150,
                                 "sk2"      :  "huagong-dafa",
                                 "lv2"      :  150,
                                 "sk3"      :  "poison",
                                 "lv3"      :  120,
                                 "shen"     :  -6000,
                                 "family/gongji" :  600 ]));
                  break;

             case "������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chanhun-suo/suo",
                                 "name"     :  "������",
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  70,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "shen"     :  -6500,
                                 "family/gongji" :  400 ]));
                  break;

             case "������צ":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/sanyin-zhua/zhua",
                                 "name"     :  "������צ",
                                 "sk1"      :  "sanyin-zhua",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  100,
                                 "shen"     :  -7000,
                                 "family/gongji" :  500 ]));
                  break;

             case "׷��צ":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/sanyin-zhua/zhui",
                                 "name"     :  "׷��צ",
                                 "sk1"      :  "sanyin-zhua",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  100,
                                 "shen"     :  -7000,
                                 "family/gongji" :  500 ]));
                  break;

             case "��ʬ��":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/shi",
                                 "name"     :  "��ʬ��",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "sk3"      :  "poison",
                                 "lv3"      :  150,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  120,
                                 "shen"     :  -10000,
                                 "neili"    :  1200,
                                 "family/gongji" :  500 ]));
                  break;

             default :
                  return 0;

        }
}

/*
void unconcious()
{
        die();
}
*/

string ask_job()
{
        object me, ob;
        mapping fam;
        int shen, exp;
        me = this_player();
        fam=query("family", me);
        shen=query("shen", me);
        exp=query("combat_exp", me);

        if(!fam) return "���ó��������̬�ȹ������β��������������أ�";
        if( fam["family_name"] != "������" && !query_temp("ding_flatter", me) )
                return "������ɵ�̬�ȿ���ȥ��̫��������";
        if(exp<500000)
                return "�����������ټӰ��������ɡ�";
        if(exp>=750000)
                return "�������������Ҳ�̫��������Լ�ȥ���������˼Ұɡ�";
        if(me->query_condition("wait_xx_task"))
                return "�ϴθ����ˣ������͵ȵȰɡ�";
        if( interactive(me) && query_temp("xx_job", me) )
                return "����ô�������﷢����";
        if(interactive(me) && me->query_condition("wait_xx_task"))
                return "�����������黹�ã���������Ϊ�����ǡ�";
        if(query("di_count") < 1)
                return "�����������黹�ã�������������ˡ�";
        ob = new(__DIR__"obj/di");
        addn("di_count", -1);
        ob->move(me);
        set("name", MAG"����̵�"NOR, ob);
        set("long", MAG"����Ѷ̵ó��棬ֻ�����ߴ�������ͨ���Ϻ죬��Ө�ɰ���\n"NOR, ob);
        set("xx_user", getuid(me), ob);
        if(fam["family_name"] != "������")
                set_temp("apply/short", ({MAG"�������ſ�"NOR+me->name()+"("+query("id", me)+")"}), me);
        set_temp("xx_job", 1, me);
        message_vision("\n$N�ó�һֻ���ƶ̵ѣ�����$n��\n", this_object(), me);
        return "����������鲻�ѣ����Ҫ���Ϊ�����˼ҷ��ǲ��ǣ�\n";
}
