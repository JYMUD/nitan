#include <ansi.h>
#include "xueshan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

string ask_fashi();
string ask_for_join();
void create()
{
        set_name("���ײ�", ({ "ge lunbu", "ge", "lunbu" }));
        set("long", @LONG
���ײ���ѩɽ�»���ɮ����ͷ�졣ͬʱ����
���Ӵ����书����һ����ɫ���ģ�ͷ��ɮñ��
LONG);
        set("title", "ѩɽ��ɮ��ͷ��");
        set("gender", "����");
        set("class", "bonze");
        set("age", 30);
        set("attitude", "heroism");
        set("shen_type", -1);

        set("str", 30);
        set("int", 20);
        set("con", 28);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 2000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 80);
        set("level", 15);
        set("combat_exp", 300000);

        set_skill("force", 120);
        set_skill("mizong-neigong", 120);
        set_skill("dodge", 120);
        set_skill("shenkong-xing", 120);
        set_skill("hammer", 140);
        set_skill("staff", 140);
        set_skill("xiangmo-chu", 140);
        set_skill("hand", 120);
        set_skill("dashou-yin", 120);
        set_skill("cuff", 120);
        set_skill("yujiamu-quan", 120);
        set_skill("parry", 120);
        set_skill("lamaism", 100);
        set_skill("literate", 80);
        set_skill("sanscrit", 200);
        set_skill("martial-cognize", 100);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "xiangmo-chu");
        map_skill("hammer", "xiangmo-chu");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.hong" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }));

        create_family("ѩɽ��", 5, "����");

        set("inquiry",([
                "���" : (: ask_for_join :),
                "����" : (: ask_for_join :),
                "׼������" : (: ask_fashi :),
                "����" : (: ask_fashi :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/xueshan/neidian",
                   "id"        : "jinlun fawang", ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "��$n" CYN "��ȵ���"
                                "�����վס������ѩɽ�������ɵ���"
                                "������߶��ط���" NOR,
                "refuse_carry": CYN "$N" CYN "��$n" CYN "�ȵ�����"
                                "���ϱ�����ʲô�ˣ���������ҷ���"
                                "����" NOR,
        ]));

        set("master_ob", 1);
        setup();

        carry_object("/d/xueshan/obj/b-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
        carry_object("/d/xueshan/obj/senggun")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "����" )
        {
                command("say ��ϰ�����ڹ���Ҫ����֮�塣");
                command("say ��λ" + RANK_D->query_respect(ob) + "������"
                        "�ذɣ�");
                return;
        }

        command("say ��Ȼ������ϰ�䣬�Ҿʹ���һЩ�书�ɣ�");
        if( query("class", ob) != "bonze" )
        {
                command("say ����������������ϲ��书��ȴ�ǵ���" HIY "��"
                        "��" NOR + CYN "���ɡ�" NOR);
                set("title", "ѩɽ���׼ҵ���", ob);
        }
        command("recruit "+query("id", ob));
}

void init()
{
        object ob;

        add_action("do_kneel", "kneel");
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        int bonus, exp_bonus;

//      if( environment(ob)->query("short") == "ѩɽ��̳" )
        if( !query_temp("������", ob))return ;
        {
                message_vision("���ײ�����ææ�Ը�С����������̳����񣬵����͡�\n\n", ob);
                message_vision(HIR"$N��ȼ�˼�̳�е�ľ�������ͣ������һ�������\n", ob);
                message_vision(HIB"һ˿����������̳��ȽȽ���𡣻�����$N�𷨸��٣��ǻ���ȥ��\n", ob);
                message_vision(RED"$N����­������һ��ˮ�����ۡ���һ���͵س������ܻ����罫��ȥ��\n", ob);
                message_vision(HIC"$N���ȴ�����������̣����������дǣ�������һ˿������$N��ǰ���۳��Ρ�\n", ob);
                message_vision(HIG"����Խ��Խ�࣬��Ȼ�ʳ����Σ�$N��ָ���Σ��������ԣ�ָ������֮·��\n", ob);
                message_vision(HIW"$N�ֳַ��壬���߱�ҡ�������ж��ܴ����䡣ͻȻ���һ��������������\n", ob);
                message_vision(HIY"��Ժ���â����һ����������ָֻ���ƽ����������ϡ�\n"NOR, ob);
                if( query_temp("������", ob)>query("combat_exp", ob) )
                {
                        //�� ���ȶ���ľ���߹��㣬�����������档����������ң�����ʮ���ơ���
//                      bonus=(ob->query_temp("������") - ob->query("combat_exp")) * ob->query_skill("lamaism",1) / 200;
                        bonus= ob->query_skill("lamaism",1) / 4;
                        exp_bonus=query("combat_exp", ob)*2*bonus/10000;
                        if (exp_bonus> 2000) exp_bonus= 2000;
                        if( query_temp("��ҷ���", ob) )
                                addn("combat_exp", exp_bonus, ob);
                        else
                                addn("combat_exp", exp_bonus/10, ob);
                }
                else
                        message_vision(HIR"\n$N��֪���������˸�����ɷ�н��µ������ȣ������ǰ�æ�ˡ�\n"NOR, ob);
                delete_temp("������", ob);
        }
}

string ask_fashi()
{
        mapping fam;
        object ob = this_player();

        if( query("short", environment(this_object())) != "ѩɽ��ɽ��" )
                return "�������������£���û�����᣿";
        if( !(fam=query("family", ob)) || fam["family_name"] != "ѩɽ��" )
                return "����������������ë�棬Ҳ������ƨ���£�";
        if ( ob->query_skill("lamaism",1) < 30)
                return "��������ķ�����ú��أ�û�����㿪̳�����¡�";
        set_temp("����", 1, ob);
        return "��λ������Ҫ����λʩ��������ѽ��";
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( query("money_id", ob) && ob->value() >= 100 )
        {
                message_vision("���ײ�Ц�Ŷ�$N˵���ã���λ"+RANK_D->query_respect(who) + "Ҫ����������ɡ�\n", who);
                set_temp("marks/xueshangate", 1, this_player());
                return 1;
        }
        if( !query_temp("����", who) )
        {
                message_vision("���ײ�Ц�Ŷ�$N˵�����ֳ�����������ʲô�ã��������Լ����Űɣ�\n", who);
                return 0 ;
        }
        delete_temp("����", who);
        if( query("id", ob) == "corpse" )
        {
                message_vision("���ײ�Ц�Ŷ�$N˵��������ȥ��̳�ɣ�\n", who);
                set_temp("������",query("combat_exp",  ob), who);
                if( query("userp", ob) )
                        set_temp("��ҷ���", 1, who);
//              who->set_leader(this_object());
//              command("go north");
//              command("go west");
//              command("go south");
                message_vision("���ײ��������뿪��\n", who);
                this_object()->move("/d/xueshan/jitan");
                return 1;
        }
        else
                message_vision("���ײ���$N˵�����ֶ������������£�ֱ������ʡ�¡�\n", who);
        return 0;
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "���Ѿ��ǳ������ˣ�����������Щʲô��";

        if( query("gender", me) != "����" )
                return "����ѩɽ������ֻ����ͽ���㻹���߰ɡ�";

        set_temp("pending/join_bonze", 1, me);

        return "���ã����ã�������������ҷ������(kneel)�ܽ䡣";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(HIC "\n$N" HIC "��˫�ֺ�ʮ�����������ع���������\n\n"
                       NOR + CYN "$n" CYN "����$N" CYN "˵�����ðɣ��Ժ����"
                       "�ڱ������аɡ�\n\n" HIY "$n" HIY "������ƣ���$N" HIY
                       "ͷ�������Ħ���˼��£��漴�㽫$N" HIY "��ͷ��������"
                       "ȥ��\n\n" NOR, me, this_object());

        set("class", "bonze", me);
        set("title", "ѩɽ������", me);

        command("nod");
        command("say ��Ȼ���˼ң��͵�һ������ٲ��ܻ��ס�");

        return 1;
}
