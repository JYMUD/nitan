// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
int ask_me();
int ask_heal();
int ask_poison();
void create()
{
        set_name("ѦĽ��", ({ "xue muhua", "xue", "muhua" }));
        set("long", "�����Ǻų������е���ҽѦĽ������˵��\n"
                    "��ͨҽ����������������\n");
        set("gender", "����");
        set("title", "��ң�ɺ��Ȱ���");
        set("nickname", HIM "������" NOR);
        set("age", 50);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);

        set("inquiry", ([
                "����" : (:ask_me:),
                "�β�"  : (: ask_heal :),
                "�ⶾ"  : (: ask_poison :),
        ]) );

        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 1000000);

        set_skill("force", 160);
        set_skill("xiaowuxiang", 160);
        set_skill("dodge", 140);
        set_skill("feiyan-zoubi", 140);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("hand", 160);
        set_skill("qingyun-shou", 160);
        set_skill("parry", 160);
        set_skill("blade", 140);
        set_skill("ruyi-dao", 140);
        set_skill("xiaoyao-qixue", 220);
        set_skill("medical", 220);
        set_skill("literate", 120);
        set_skill("martial-cognize", 140);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyang-zhang");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("��ң��", 3, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("sigh");
                command("say ��Ȼ��˵���ܲ�׾�����ǡ����ҿ��㻹���߰ɡ�");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 30)
        {
                command("sigh");
                command("say �������ŵ������ķ���û��ѧ�ã�����������㣿");
                return;
        }

        command("say �ðɣ��Ҿ��������ˣ��Ժ�Ҫ��Ϊ��ң�ɳ�������");
        command("recruit "+query("id", ob));
}

int ask_me()
{
        object ob=this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say ������û�գ�");
                return 1;
        }

        if( query("count", me)<1 )
        {
                command("say ��ҩ�������ˣ��һ�û���ü��䣬��һ�������ɡ�");
                return 1;
        }
        if( query("shen", ob)<0 )
        {
                command("say �������������ҿɲ���Ϊ�����ˣ�");
                return 1;
        }
        if( query("score", ob)<300 && query("combat_exp", ob)>100500 )
        {
                command("say ����㽭��������Ҳ������Ϊ�����ˣ�");
                return 1;
        }
        if( query("eff_qi", ob) == query("max_qi", ob )
         && query("eff_jing", ob) == query("max_jing", ob) )
        {
                command("?"+query("id", ob));
                command("say ��û�����κ��˰���");
                return 1;
        }
        else
        {
                message_vision("ѦĽ��ι$N����һ��ҩ�裬Ȼ����ϥ���£�˫������$N�ı��ġ�\n", ob);
                if( query("combat_exp", ob)>100500 )
                {
                        if( query("family/family_name", ob) != "��ң��" )
                                addn("score", -200, ob);
                        else addn("score", -100, ob);
                }
                set_temp("busy", 1, me);
                ob->start_busy(2);
                addn("count",-1);
                remove_call_out("recover");
                call_out("recover",2,ob);
                if( query("count", me)<1 )
                {
                        where = environment(me);
                        addn("no_fight", 1, where);
                        remove_call_out("newyao");
                        call_out("newyao",1800,me);
                }
                return 1;
        }
}


int recover(object ob)
{
        delete_temp("busy", this_object());
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        message_vision("��Լ����һ�Ѳ��ʱ�֣�ѦĽ��������վ��������\n",ob);
        command("say ��������Ѿ�ȫ���ˣ�����������");
        return 1;
}
int newyao(object me)
{
        object where = environment(me);
        delete_temp("busy", this_object());
        addn("count", 30, me);
        addn("no_fight", -1, where);
        return 1;
}

int ask_heal()
{
        object ob = this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say ������û�գ�");
                return 1;
        }

        if( query("shen", ob)<0 )
        {
                command("say �������������ҿɲ���Ϊ���β���");
                return 1;
        }
        if( query("score", ob)<300 && query("combat_exp", ob)>100000 )
        {
                command("say ����㽭��������Ҳ������Ϊ���β���");
                return 1;
        }

        if( ob->query_condition("ill_kesou")
            || ob->query_condition("ill_zhongshu")
            ||ob->query_condition("ill_shanghan")
            ||ob->query_condition("ill_dongshang")
            ||ob->query_condition("ill_fashao"))
        {
                message_vision("ѦĽ�����$N���ţ���һ˼�������ת���ҩ¨��ȡ����ζ��ҩ����ʼΪ$N��ҩ��\n", ob);
                if( query("combat_exp", ob)>100000 )
                {
                        if( query("family/family_name", ob) != "��ң��" )
                                addn("score", -200, ob);
                        else addn("score", -100, ob);
                }
                addn("count", -1, me);
                set_temp("busy", 1, me);
                ob->start_busy(5);
                remove_call_out("recover_II");
                call_out("recover_II",5,ob);
                return 1;
        }

        else
        {
                command("?"+query("id", ob));
                command("say �������ɫ����û����������");
                return 1;
        }

}
int recover_II(object ob)
{
        delete_temp("busy", this_object());
        if (ob->query_condition("ill_kesou"))
                ob->clear_condition("ill_kesou",0);
        if (ob->query_condition("ill_zhongshu"))
                ob->clear_condition("ill_zhongshu",0);
        if (ob->query_condition("ill_shanghan"))
                ob->clear_condition("ill_shanghan",0);
        if (ob->query_condition("ill_dongshang"))
                ob->clear_condition("ill_dongshang",0);
        if (ob->query_condition("ill_fashao"))
                ob->clear_condition("ill_fashao",0);
        message_vision("��Լһ�������ѦĽ���������һ��հ��õ��������ڵ���ҩ��\n",ob);
        command("say ����������޴�,����������");
        return 1;
}


int ask_poison()
{
        object ob = this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say ������û�գ�");
                return 1;
        }

        if( query("shen", ob)<0 )
        {
                command("say �������������ҿɲ���Ϊ��ⶾ��");
                return 1;
        }
        if( query("score", ob)<500 && query("combat_exp", ob)>100000 )
        {
                command("say ����㽭��������Ҳ������Ϊ��ⶾ��");
                return 1;
        }

        if( ob->query_condition("chanchu_poison")
            || ob->query_condition("drunk")
            ||ob->query_condition("flower_poison")
            ||ob->query_condition("ice_poison")
            ||ob->query_condition("iceshock")
            || ob->query_condition("rose_poison")
            ||ob->query_condition("scorpion_poison")
            ||ob->query_condition("slumber_drug")
            || ob->query_condition("snake_poison")
        //   ||ob->query_condition("ss_poison")
            ||ob->query_condition("wugong_poison")
        //   || ob->query_condition("xx_poison")
            ||ob->query_condition("xiezi_poison")
            ||ob->query_condition("zhizhu_poison")
            || ob->query_condition("zhua_poison")
            ||ob->query_condition("ice_sting"))
        {
                message_vision("ѦĽ�����$N���ţ�˫ü���������ι$N����һ��ҩ�裬��ϥ���£�˫������$N�ı��ģ���ʼΪ$N�ⶾ��\n", ob);
                if( query("combat_exp", ob)>100000 )
                {
                        if( query("family/family_name", ob) != "��ң��" )
                                addn("score", -300, ob);
                        else addn("score", -200, ob);
                }
                addn("count", -1, me);
                set_temp("busy", 1, me);
                ob->start_busy(5);
                remove_call_out("recover_III");
                call_out("recover_III",5,ob);
                return 1;
        }

        else
        {
                command("?"+query("id", ob));
                command("say �����Ұﲻ����ʲôæ�ˣ�");
                return 1;
        }

}
int recover_III(object ob)
{
        delete_temp("busy", this_object());
        if (ob->query_condition("chanchu_poison"))
                ob->clear_condition("chanchu_poison",0);
        if (ob->query_condition("drunk"))
                ob->clear_condition("drunk",0);
        if (ob->query_condition("flower_poison"))
                ob->clear_condition("flower_poison",0);
        if (ob->query_condition("ice_poison"))
                ob->clear_condition("ice_poison",0);
        if (ob->query_condition("iceshock"))
                ob->clear_condition("iceshock",0);
        if (ob->query_condition("rose_poison"))
                ob->clear_condition("rose_poison",0);
        if (ob->query_condition("scorpion_poison"))
                ob->clear_condition("scorpion_poison",0);
        if (ob->query_condition("slumber_drug"))
                ob->clear_condition("slumber_drug",0);
        if (ob->query_condition("snake_poison"))
                ob->clear_condition("snake_poison",0);
//      if (ob->query_condition("ss_poison"))
//              ob->clear_condition("ss_poison",0);
        if (ob->query_condition("wugong_poison"))
                ob->clear_condition("wugong_poison",0);
//      if (ob->query_condition("xx_poison"))
//              ob->clear_condition("xx_poison",0);
        if (ob->query_condition("xiezi_poison"))
                ob->clear_condition("xiezi_poison",0);
        if (ob->query_condition("zhizhu_poison"))
                ob->clear_condition("zhizhu_poison",0);
        if (ob->query_condition("zhua_poison"))
                ob->clear_condition("zhua_poison",0);
        if (ob->query_condition("ice_sting"))
                ob->clear_condition("ice_sting", 0);
        message_vision("��Լһ�������$N�³�һ����Ѫ��ѦĽ��������վ��������\n",ob);
        command("say �����ڶ�������,����������");
        return 1;
}
