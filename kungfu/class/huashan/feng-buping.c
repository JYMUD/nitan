// This program is a part of NITAN MudLIB
// feng-buping.c  �ⲻƽ

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "jianzong.h"

mixed ask_feilong();
mixed ask_sanxian();
string ask_me();
mixed ask_sword_martial();

void create()
{
        set_name("�ⲻƽ", ({ "feng buping", "feng" }) );
        set("gender", "����");
        set("class", "swordsman");
        set("title", "��ɽ���ڵ�ʮ��������");
        set("age", 45);
        set("long", "�ⲻƽ�ǻ�ɽ���ڵ�һ���֣���������һ�Żƽ�������Ƥ��\n");
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 6300);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 3000000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.piao" :),
                (: perform_action, "cuff.song" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 400);
        set_skill("cuff", 400);
        set_skill("strike", 400);
        set_skill("hunyuan-zhang", 400);
        set_skill("sword", 600);
        set_skill("force", 400);
        set_skill("parry", 400);
        set_skill("dodge", 400);
        set_skill("literate", 400);
        set_skill("huashan-sword", 400);
        set_skill("kuangfeng-jian", 600);
        set_skill("huashan-neigong", 400);
        set_skill("huashan-quan", 400);
        set_skill("poyu-quan", 400);
        set_skill("huashan-shenfa", 400);
        set_skill("jianyi", 600); 
        set_skill("martial-cognize", 400);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("strike", "hunyuan-zhang");
        map_skill("unarmed", "huashan-quan");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set("no_teach", ([
                // "kuangfeng-jian" : "����ѧ�Ļ��������ҳ�ʦ�ܰɣ�\n",
        ]));

        set("inquiry", ([
                "����"     : "�ҽ��ڽ������棬����ѧ���ž��У�\n",
                "����"     : "�ҽ��ڽ������棬����ѧ���ž��У�\n",
                "����"     : "�Ҿ��ǽ��ڴ��ˣ�\n",
                "���콣" : "����ѧ�Ļ��������ҳ�ʦ�ܰɣ�\n",
                "����"     : "�ߣ������书ӹ�ײ����������ὣ�����߰��㡣\n",
                "����Ⱥ"   : "������α���ӣ��ɶ�\n",
                "��ɽ����" : "�Ǳ��Ǳ��ɾ�ѧ������һ��һ�Ľ����������ǡ����������һ�У��ɽ�ɱ�У������ܵ���\n",
                "������"   : "�������Ѷ��겻����ʦ�壬������������䡣\n",
                "��������" : (: ask_sword_martial :),
                "�������" : (: ask_me :),
        ]));

        set_temp("apply/attack", 220);
        set_temp("apply/defense", 220);
        set_temp("apply/damage", 400);
        set_temp("apply/unarmed_damage", 400);

        create_family("��ɽ����", 13, "����");

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_ask(object me, string topic)
{
        if( query("family/family_name", me) != "��ɽ����" )
                return 0;

        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "������ӿ" :
                if( query("max_neili", me)>1000000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say �ҽ����Խ���Ϊ������Ϊ�Σ�����ڹ���Ϊ������������;���ٲ����������ڽ�����");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuangfeng-jian/yong",
                           "name"    : "������ӿ",
                           "sk1"     : "kuangfeng-jian",
                           "lv1"     : 140,
                           "gongxian": 800,
                           "sk2"     : "dodge",
                           "lv2"     : 140, ]));
                break;

        case "�����������ɽ�" :
                if( query("max_neili", me)>1000000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say �ҽ����Խ���Ϊ������Ϊ�Σ�����ڹ���Ϊ������������;���ٲ����������ڽ�����");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/xian",
                           "name"    : "�����������ɽ�",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 160,
                           "free"    : 1,
                           "gongxian": 1000,
                           "sk2"     : "dodge",
                           "lv2"     : 160, ]));
                break;

        default:
                return 0;
        }
}

void attempt_apprentice(object ob)
{
        if (query("apprentice_available"))
        {
                if (find_call_out("do_recruit") != -1)
                        command("say ������һ��һ������");
                else
                        call_out("do_recruit", 2, ob);
        } else
        {
                command("say �Ϸ�����Ѿ������������ӣ���������ͽ�ˡ�");
        }
}

void do_recruit(object ob)
{
        if( query("int", ob)<20 )
                command("say �һ�ɽ���Խ���Ϊ�������ҿ�" + RANK_D->query_respect(ob) + "���ʺ���ѧ������");
        else
        {
                command("say �ã��ã��ã��ܺá�");
                command("recruit "+query("id", ob));
        }
}

int recruit_apprentice(object ob)
{
        if (::recruit_apprentice(ob))
        {
                set("title", "��ɽ���ڵ�ʮ�Ĵ�����", ob);
                set("class", "swordman", ob);
        }
        addn("apprentice_availavble", -1);
}

void reset()
{
        set("apprentice_available", 3);
}

// ������Ƿ������ڵĵ���ѧϰ������������ڵ�ֱ���ҳɲ���ѯ��
string ask_me()
{
        object ob = this_player(), me = this_object();
        mapping obfam;

        obfam=query("family", ob);

        if (! obfam || obfam["family_name"] != "��ɽ��")
        {
                if (obfam && obfam["family_name"] == "��ɽ����")
                {
                        return "�㻹�����ҵ�ʦ�ܳɲ��ǰɡ�\n";
                }

                if( query_temp("feilong", ob)<3 )
                {
                        command( "sneer" );
                        addn_temp("feilong", 1, ob);
                        return "���Ǻ���ԨԴ����������ʲô�����Ǳ�̫����ĺá�\n";
                }
                else
                {
                        message_vision("$N��ɫ΢�䣬Ŀ������һ��������һ����Ц��\n", me);
                        delete_temp("feilong", ob);
                        me->kill_ob(ob);
                        remove_call_out("fast_attack");
                        call_out("fast_attack", 0, me, ob);
                        return "�������Ĵ���̽����ɽ�����İ��ܣ������ϲ⣡�Ƿ���Ա��ɲ�����\n"
                               "�㼴Ȼ�Ի�ɽ�������㿾���ֻ���û�ɽ����������·�ˡ�\n";
                }
        }

        command("look"+query("id", ob));

        if (ob->query_skill("huashan-sword", 1) < 400)
                return "��Ļ�ɽ������Ϊ������ѧ���ˡ������������";

        if (ob->query_skill("zixia-shengong", 1) < 70)
                return "�����Խ�Ϊ�ڣ�����Ϊ���������������ã������ϼ�񹦿ɵ�����һ���๦��";

        if (ob->query_skill("zixia-shengong", 1) > ob->query_skill("huashan-sword", 1))
        {
                command( "sneer" );
                return "�������ڵ��ˣ�ȴ��������̣�������ε�������";
        }

        if( query("can_perform/huashan-sword/long", ob) )
                return "�ף��Ҳ��Ǵ����㡸����������𣿶��¹���ú���ϰ������˻�ɽ���ڵ�������";

        command("say �ã��ұ㴫�㡸���������������ϸ�ˣ�" );

        message_vision("$N�������ߣ��׹���磬���ش���ɽ��Ρ�ţ����鴦������޼������Ī�⡣\n" +
                       "�赽������$Nһ����ȣ��������ַɳ�������һ�����磬ֱû��������һ�����С�\n", me);

        set("can_perform/huashan-sword/long", 1, ob);

        return "�����Ҫ�ڼ���ϰ���𹼸����ҵ�һ���̵���";
}

int fast_attack(object me, object ob)
{
        int i, num;

        if( !query_temp("weapon", me))return 1;
        num = random(2) + 3;

        message_combatd(RED "\n�ⲻƽ��ɫ���أ�ʹ������������콣�����˽�����Ƶ����$N������" + chinese_number(num) + "����\n" NOR, ob);

        for (i = 1; i < num + 1; i++)
        {
                if (! me->is_fighting(ob)) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        }

        return 1;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huashan-sword/feilong", me) )
                return "�㻹����ȥ��ϰ�书��һѩ���ǽ����߳ܣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�������ǻ�ɽ���ڵ��ˣ����߰ɣ�";

        if (me->query_skill("huashan-sword", 1) < 150)
                return "��Ļ�ɽ�����������ң���Ҫ�ٸ��Ҷ����ˣ�";

        message_vision(HIY "$n" HIY "���һ��������ճ��һ��ʯ��"
                       "�����������������ͻȻ������ĩ��\n"
                       HIY "$n" HIY "��ͷ������$N" HIY "������һ"
                       "��ûʲôϡ�棬����Ҫ��������������������"
                       "����Ϊ���ڵ��ӣ�ҲҪ�ú�����������\n" NOR,
                       me, this_object());
        tell_object(me, HIG "��ѧ�������������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        set("can_perform/huashan-sword/feilong", 1, me);
        return 1;
}
*/


mixed ask_sword_martial()
{
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "�������������Լ�Ҫ�ڼ���������";

        if( query("combat_exp", me)<200000 )
                return "������书Ҳ��������̽�������úø�������ȥ��";

        if (me->query_skill("sword-cognize", 1) < 50)
                return "����޽����������������������̸���а��";

        if (me->query_skill("sword-cognize", 1) >= 200)
                return "�㽣���˽���Ѿ������ˣ�����ûʲô���ٽ�����ˡ�";

        if( query_temp("last_ask/murongbo/martial", me)+240>time() )
                return "������̸�ɣ�������Ҫ�����룬�ú������ᡣ";

        message_vision("$N����$n���������ðɣ��Ҿ�����̸̸���ڽ���������ĵá���\n",
                       this_object(), me);

        if( query("potential", me)-query("learned_points", me)<100 )
        {
                tell_object(me, "���������Ժ����ģ�û����������Ȼ��������Ǳ�ܲ�����\n");
                return 1;
        }

        addn("learned_points", 100, me);
        tell_object(me, HIG "���������л�Ȼ���ʣ�ͨ���˲��ٽ����İ��\n" NOR);
        set_temp("last_ask/murongbo/martial", time(), me);
        me->improve_skill("sword-cognize", 1500 + random(2000));
        return 1;
}
