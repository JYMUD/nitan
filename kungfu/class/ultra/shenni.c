// shenni �Ϻ�����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;


#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "�ڼҹ���" NOR
#define MY_OPINION      "force"

#define QUEST_SN_D(x)   ("/quest/questsn/quest/questsn" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define SNMSG_D         ("/quest/questsn/quest/shenni-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string* sn_msg = ({
        "�Ϻ�����΢Ц��˵����",
        "�Ϻ���������۾�ڤ˼Ƭ�̵�����",
        "�Ϻ������ͷ�����룬˵������",
        "�Ϻ������������֣�˵������",
        "�Ϻ�����΢΢Ц��Ц������",
});

string* qin_msg1 = ({
        "���������ǵ����ѣ�����name����Ӱ������̬������������Ҳ�Ϳ����ˣ�",
        "����˵name����ķ�ֳ��Ӱ���˵��ص���̬���������ǲ�Ӧ�����ɱ���",
        "�ѵ�nameҲ�����������鷳������ϡ�棬�ҵ����뿴������",
        "������Ļ�԰���źܶ�Ķ������û��name��",
        "�ڿ��е�ʱ�򣬿�������������ܹ�����������name��ʵͦ�ɰ��ģ�",
        "���������һ����ϲ��������ˣ�������name�������͸�����������ò�����",
        "�����ϴ��ɱɱ�ģ��ٲ�����nameҲ�����޹����ۣ������ı�������",
});

string* qin_msg2 = ({
        "��ȥ���������������ɡ���",
        "ȥ�ҵ�����������������",
        "���ܰ�������������ô����",
        "�������һ��ȥ���Ұ��������ɡ���",
        "����Ū�����ҡ���",
});

string  *my_opinions = ({ "force" });

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void create()
{
        set_name("�Ϻ�����", ({ "nanhai shenni", "shenni", "nanhai" }) );
        set("title", HIG "����ʦ" NOR);
        set("gender", "Ů��");
        set("age", 91);
        set("long", "����һλ�������ᣬ��������ʲô��ͬ��\n");
        set("attitude", "peaceful");
        set("class", "bonze");
        set("no_get", 1);
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 70);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "��ָ��ͨ" : "�����ұ̺��񹦹���ָ������ı仯�������ҵ��������������ڸ�һ�ˡ�",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "�ú�����Լ�����ѧ����(martial-cognize)����ʱ��ʲô�书����С���ƣ�",
                "����" : "�����׺ݵ����������ɵ��ˣ�������������������(quest)��\n",
                "�Թ�"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("staff", 500);
        set_skill("bluesea-force", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "bluesea-force");
        map_skill("force", "bluesea-force");
        map_skill("dodge", "bluesea-force");
        map_skill("finger", "bluesea-force");
        map_skill("strike", "bluesea-force");
        map_skill("staff", "bluesea-force");

        prepare_skill("finger", "bluesea-force");
        prepare_skill("strike", "bluesea-force");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "����");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhubang")->wield();

        set("startroom", "/d/xiakedao/zhuwu2");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision("$Nü��΢΢һ����\n", this_object(), me);
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_sn", me);

        if (!quest)
                return "�㲢û�н��ҵ������������Թ��������ʲô��";

        if ( undefinedp(quest["maze"]) )
                return "��ӵ�������Թ��޹ذ�����ʲô�����أ�";
        /*
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "������������޷���������Ǹ��Թ���˵�Ѿ���ʧ�ˡ�";

        message_vision("$N��$n��ͷ��������Ȼ���Ѿ�׼����Ҫȥ����Ǿ�ף��һ��˳������\n", ob, me);
        //me->move(maze["entry"]);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "�ߣ�������书Ҳ�����������ۣ�";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "�����ˣ����ڹ��������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�Ҫ�Ǻ�ƶ����ϼ���Ҳ����";

        if (is_fighting(me))
                return "��������ʲô������Ӯ���ң����Լ����Լ����۰ɣ�";

        if (me->is_fighting())
                return "��Ȼ���ɣ����Ҹ������ǡ�";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say ����ʲô������Ҫ���ҡ�");
                        return 1;
                }

                message_vision("$N��Ϊ��ŭ�Ķ�$n������û������æ���𣿡�\n",
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/shenni", me) )
        {
        case 0:
                command("say �ðɣ����ǹ�һ�У�����һ��������");
                break;
        case 1:
                command("say ��׼����û�У����˾����ɡ�");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ����ұ���������죡");
                return 1;
        }

        addn_temp("want_opinion/shenni", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        if( query("max_neili", me)>4000)lvl+=20;
        return lvl;
}

void do_congration(object me)
{
        command("chat �����������ǲ���");
}

int accept_hit(object me)
{
        command("heng");
        command("say �����" + RANK_D->query_rude(me) + "���������ҵ������ˣ�");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision("$N��$n�������ܺã���Ҳ������ʦ�����ˣ�"
                               "���ɣ����ǱȻ�һ�£���\n",
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/shenni", me) )
        {
                command("say ���ʲôҪ���Ҷ��֣�");
                return 0;
        }

        command("look "+query("id", me));

        COMBAT_D->do_attack(this_object(), me, 0);

        if( query("qi", me) <= 0 )
        {
                message_vision("\n$Nҡҡͷ��$n�����������ڵ��书"
                               "�����Զ������һ�ж��Ӳ�ס����\n",
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        message_combatd("$N�������������$n������ԣ�����ͬʱ����������"
                       "��һ���ֻ������ͷ����������������\n��Ȼ$N����"
                       "һ�����ջع�����û��һ�����ͣ�������$n��Ϊ�Ȼ��\n",
                       this_object(), me);
        if( query("neili", me)<3000 )
        {
                message_vision("$Nҡҡͷ��$n�������ʲ����������㣬����"
                               "�Ժ��������㽫�����������������ɣ���\n",
                               this_object(), me);
                return notify_fail("�������ǻ�ȥ����һ�������ɣ�\n");
        }
        set("neili", 0, me);


        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision("\n$Nһ���ֵ��������ˣ��������롣��\n",
                       this_object(), me);
        return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision("$N��ŭ����������С����ʲô"
                               "�ң����ҹ�����˵��һ�ư�$n�����ڵء�\n",
                               this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "�ĺ�����" && query("character", me) != "��ʿ��˫" )
        {
                command("say ���������Բ����������²��˺��ģ�"
                        "��û����Ȥ���㣡");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵı̺��񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "bluesea-force")
                return 1;

        if( query_temp("can_learn/shenni/bluesea-force", me) )
                return 1;


        set_temp("can_learn/dugu/bluesea-force", 1, me);
        command("nod");
        command("say �����ҽ����ҵľ�ѧ�̺��񹦣��ܲ���ѧ��"
                "�Ϳ�����컯�ˣ�");
        return 1;

        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
        command("chat �գ��գ��գ�ƶ��ȥҲ��");
        destruct(this_object());
        */
        full_self();
        return;
}

void die()
{
        /*
        message("vision", "\n"HIR + name() + "���һ����������һ����"
                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
        command("chat ƶ��ȥҲ��");
        destruct(this_object());
        */
        full_self();
        return;
}

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc,the_ob;
    int i, giveup,tag,want,lev,lev1,time;
    int exp;
    int lvl,all_lvl;
    string msg,*sname,place,the_race;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "���ռ�թ") && 
            (query("character", me) != "��ʿ��˫") && 
            (query("character", me) != "�ĺ�����") )
    {
        write("�Ϻ�����ҡͷ������������ʵ��������½��������̫�����Ĵ������������ұ���Ҫ����ɡ�\n");
        return 1;
    }
    /*
    if( !(query("shen", me)>0) )
    {
        write("�Ϻ����ῴ����ֻ��ҡͷ�������߽���������Ҫ������Ȼ�ҽ�����ɱֹɱ��������а��̫�أ��������˰ɣ���\n");
        return 1;
    }
    */
    if(exp < 500000)
    {
        write("�Ϻ�����΢Ц������������Դ����������ڵľ��飬��������ʵ��̫��Σ�գ��ú�ȥ������������ͷ�������ҡ�\n");
        return 1;
    }


    if( quest=query("quest_sn", me) )
    {
        write("�Ϻ�����Ǻ�Ц��˵���ļ����ǺȲ������డ����Ҫ�ż�����������\n");
        return 1;
    }

    if( mapp(query("quest_kh", me)) )
    {
        write("�Ϻ�����΢΢һ��˵������̫�಻�Ǹ�����������ô��Ҫ���㻹���������ͷ������ɡ�\n");
        return 1;
    }


    giveup=query_temp("sn_giveup", me);
    if( (time()-query("questsn_giveup_time", me))<20+giveup*2 && !wizardp(me) )
    {
        write("�Ϻ�����Ц�Ŷ���˵��������ô�겻��������ô��˳������Ҫ�ż����Ⱥú�����ԭ�������\n");
        return 1;
    }

/*
    if( query("questsn_times", me)<3
         || (query("questsn_times", me)>5 && random(20) == 5) )
    {
        X_QuestD->query_quest(me, this_object());
        return 1;
    }
*/

    quest = ([]);
    // ���¸�����
    if(exp <= 600000)        tag = 0;
    else if(exp <= 900000)   tag = 1;
    else if(exp <= 1200000)  tag = 2;
    else if(exp <= 1800000)  tag = 3;
    else if(exp <= 2500000)  tag = 4-random(3);
    else if(exp <= 3200000)  tag = 5-random(3);
    else if(exp <= 4000000)  tag = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(10)==0))
            tag=8;
        else tag=7-random(3);
    }

    i=query("questsn_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"�Ϻ�����ǺǴ�Ц�����˵�˵��������İ��������治����\n"+msg
            +"\n���뷨Ūһ��"+qgood["name"]+"������ԼҪ "+want+" "+qgood["unit"]+"���ж��ٿ����Ƚ����١�ȥ�գ���\n"NOR;
        write(msg);
        quest = ([
                   "id"         : qgood["id"],
                   "name"       : qgood["name"],
                   "msg"        : msg,
                   "want"       : want,
                   "type"       : "��",
                   "check_file" : qgood["check_file"],
                   "level"      : tag,
                   "bonus"      : 0,
                   "all_bonus"  : 0,
                ]),
        set("quest_sn", quest, me);
        return 1;
    }

    if(tag==8)
    {
        npc = new(CLASS_D("generate") + "/player_npc.c");
        FUBEN_D->clear_fuben("ultra",query("id", me));
        maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
        maze_object->set_maze_boss(npc);
        //maze_target = MAZE_D->create_maze(npc);
        maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
        npc->move(maze_target);
        npc->set_from_me(me,1);
        addn_temp("apply/attack", npc->query_skill("force")/3, npc);
        addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
        addn_temp("apply/parry", npc->query_skill("force")/3, npc);
        addn_temp("apply/damage", 200+random(100), npc);
        addn_temp("apply/unarmed_damage", 200+random(100), npc);
        addn_temp("apply/armor", 200+random(300), npc);
        set_temp("quester",query("id",  me), npc);
        set("auto_perform", 5, npc);

        set("shen", -query("combat_exp", npc)/2000, npc);
        msg="�Ϻ��������ݶ���˵����"+npc->name(1)+
            "���������Σ�����֣���˵���������һ���Թ��У���ȥ�������ɣ���\n";

        quest = ([
            "maze" : maze_object,
            "name" : npc->name(1),
            "id":query("id", npc),
            "bonus": (200+random(51)),
            "type" : "ɱ",
            "level": 8,
            "where": maze_target,
            "msg":   msg,
            "object": base_name(npc),
        ]);
        tell_object(me, quest["msg"]+"\n");
        set("quest_sn", quest, me);

        return 1;
    }
    else
    {
            if (exp > 4000000)
            {
                all_lvl = 0;
                lvl = random(28) + 1;
                for (i = 1;i < 8;i ++)
                {
                    all_lvl += i;
                    if (lvl > all_lvl - i && lvl <= all_lvl)
                    {
                        lvl = i;
                        break;
                    }
                }
            } else lvl = tag;
            while(1)
            {
                quest = QUEST_SN_D(lvl)->query_quest();
                if (quest["type"] == "ɱ" || quest["type"] == "��")
                {
                    if (! get_object(quest["object"])->is_master())
                    break;
                } else
                    break;
            }

/*
    if(undefinedp(quest["msg"]) || quest["msg"] == "")
*/
    switch(quest["type"])
    {
        case "��":
                msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                break;
        case "ɱ":
                if( query("race", get_object(quest["object"])) != "����" )
                {
                        quest["type"] = "��";
                        msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                        break;
                } else msg=SNMSG_D->query_snmsg("ɱ",quest["name"]);
                break;
        case "Ѱ":
                msg=SNMSG_D->query_snmsg("Ѱ",quest["name"]);
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/sn_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = sn_msg[random(5)]+"�㿴�ܷ���ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                        "����������һ���Թ��У��Ͻ�ȥ����Ȼ����ʱ�������ܾͲ����ˡ�";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("�Ϻ����Ὣ$N������ڵ��ϡ�\n",thing);
                } else message_vision("�Ϻ����Ὣ$N����$n��\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                quest["maze"] = maze_object;
                break;
        }
    }
    quest["msg"] = msg;
    quest["level"] = tag;

/*
    if (quest["type"] == "ɱ" && (random(6) == 3 || wizardp(me)))
    {
        robot_quest = ANTI_ROBOT->get_question();
        msg = "�Ϻ�����΢Ц��˵�������Ҹս�����ͬ�˵Ŀ��������һ�£���ȥ֪ͨһ��" + quest["name"] + NOR"���¿����ǣ�\n";
        msg += robot_quest["question"];
        msg += "��ֻ��Ҫ��������"HIR"��ͨ��������ʽ"NOR"���͹�ȥ�����ˣ����͵�ָ���ǣ�whisper��\n";
        quest["type"]   = "��";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    set("quest_sn", quest, me);
    if(stringp(quest["msg"])&&quest["msg"]!="")
                write(YEL""+quest["msg"]+"\n"NOR);
    else
    {
                write(YEL""+msg+"\n"NOR);
                set("quest_sn/msg", msg, me);
    }
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times, i,tag,all_quest_sn, bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "���ռ�թ") && (query("character", me) != "�ĺ�����") && query("character", me) != "��ʿ��˫" && !(query("shen", me)>0) )
    {
        write("�Ϻ����ᾪ�ȵĵ���������˭���������������ʲô����\n");
        return 0;
    }
    else if( !(quest=query("quest_sn", me)) )
    {
        write("�Ϻ�����Ǻ�Ц��������֪������Т���ң����ǿ��Կ�ʵ���ж�������㻹���Լ����Űɡ���\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
           if (ob->value() < 1000000)
           {
                   tell_object(me,"�Ϻ�����Ǻ�һЦ���Ҳ�ȱǮ���������Ǯ�����Լ����������԰ɡ�\n");
                   return notify_fail("�Ϻ���������˵�����������100���ƽ��Ҿ�ȡ�����������\n");
           }
           delete("quest_sn", me);
           tell_object(me,"�Ϻ��������ַ���" + ob->name(1) + "���������˵��������������������˰ɡ�\n");
           destruct(ob);
           return 1;
    }

    if(quest["type"]!="Ѱ"&&quest["type"]!="��"&&quest["type"]!="��"&&quest["type"]!="��")
    {
        write("�Ϻ�����΢Ц��������û�н���ȥ�Ҷ���ѽ���������ջء���\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("�Ϻ������ŭ�����������С�ӣ���Ȼ����ƭ�������������ˣ���������ץ��������\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(��������)����%s(%s)(%s)����\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "��" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("�Ϻ�����ӹ���һ������ü���������Ż�ִ��˭����ģ���������Ū�ң���\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("�Ϻ�����ӹ���һ������ü���������Ż�ִ�����Լ��õ���ô����������Ū�ң���\n");
            return 0;
        }
    } else if ( quest["type"] == "��" )
    {
        switch( quest["id"] )
        {
            case "HEAD_OBJ":
            case "ARMOR_OBJ":
            case "CLOTH_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            case "SWORD_OBJ":
            case "BLADE_OBJ":
            case "HAMMER_OBJ":
            case "STAFF_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("�Ϻ�����˵�������ⲻ������Ҫ�ġ���\n");
        return 0;
    }

//    message_vision("$N��$n�����Ϻ����ᡣ\n",me,ob);��give��Ϣ�ظ�haiyan
    times=query("questsn_times", me);//��������
    tag=query("quest_sn/level", me)+1;//����ȼ�
    if( (i=query("questsn_times", me))<15)i=15-i;
    else i = 1;

    exp = tag*80 + quest["bonus"]*3;
        exp += times;
    exp += random(exp/2);
    exp = exp/i;

    if (tag > 4 && i > 5)
        exp /= 2;

    if (quest["type"]=="��")
    {
        exp = quest["bonus"]*(tag + 1);
        exp += random(exp/2);
    }

    pot = exp/(2+random(2));

    score = random(exp/20);
    weiwang = random(exp/15);

    if (times + 1 > 200)
         mar = exp/5 + random(times);
    else mar = 20 + random(20);

    if (mar > 1000) mar = 1000;

    if(quest["type"]=="��")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            addn("quest_sn/ok", 1, me);
            write("�Ϻ�����ӹ������˵�˵������Ҫ�ľ���������� "+quest["ok"]+" �ˣ�̫���ˣ����� "+(quest["want"]-quest["ok"])+" ��������Ŭ������\n");
            score /= 3;
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_sn/all_bonus", exp, me);
            destruct(ob);
            return 1;
        }
        exp += quest["all_bonus"]/2;
        pot = exp/(2+random(2));
        weiwang = random(exp/15);
        mar = mar*2;
        mar += mar/4 * quest["want"];
        score = score;
    }
    write("�Ϻ�����ӹ������ĵ�Ц��˵��������ѽ�������������ɵúܺã���\n");
    destruct(ob);
    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"Ȼ��ȡ��һ���ƽ���㣺�����߽�����������Ҫ����Ǯ����������Щ���ӣ�����ȥ�ðɣ���\n"
                       HIW"\n�㱻������ "+i+" ���ƽ�\n");
        if(!gold->move(me))
        {
            message_vision("����$N���϶���̫�أ��ƽ�һ���Ӵ����л����˵��ϡ�\n",me);
            gold->move(environment());
        }
        GIFT_D->bonus(me, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                             "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
    }
    else GIFT_D->bonus(me, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar, "percent" : 100,
                              "weiwang" : weiwang, "score" : score ]), 1);

    /*
    if ( times < 1 )
        set("questsn_times", 1, me);
    else
        addn("questsn_times", 1, me);
    */
   set_temp("sn_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("questsn_times", me)+1;
   total_count = quest_count % 500;
   if (total_count == 50)
   {
       msg = "$N�Ǻ�Ц�������������㻹���ԣ�����"+chinese_number(quest_count)+
       "��������ɵ�ƯƯ����������Ŭ������\n";
        special = 1;
           } else
       if (total_count == 100)
   {
       msg = "$NЦ�ĺϲ�£�죬������һ�۵�������־����"+chinese_number(quest_count)+
       "������ɵøɾ���������\n";
       special = "/clone/gift/puti-zi";
   } else
    if (total_count == 150)
    {
        msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
        money = 1;
    } else
    if (total_count == 200)
    {
        msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
        money = 1;
    } else
    if (total_count == 250)
    {
        msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
        money = 1;
    } else

    if (total_count == 300)
    {
        msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
         special = "/clone/gift/tianxiang";
    } else
    if (total_count == 350)
    {
        msg = "$N����һ��������������ĺ��ʺ�ѧ�䣬������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
         special = "/clone/gift/tianxiang";
    } else
    if (total_count == 400)
    {
        msg = "$N̾����������һ����ѧ��Ű����벻�������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
         special = "/clone/gift/jiuzhuan";
    } else
    if (total_count == 450)
        {
        msg = "$N����������������ţ�������ţ�����������"+chinese_number(quest_count)+
               "��������һ��©�����ף����ף���\n";
        special = "/clone/gift/jiuzhuan";
    } else
       if (total_count == 0)
   {
       msg = "$N����̾�˿�����������û�뵽������"+chinese_number(quest_count)+
       "��������һʧ�֣������Ժ����������Щ��������������\n";
       special = "/clone/gift/jiuzhuan";
#ifdef DB_SAVE
       if( MEMBER_D->is_valid_member(query("id", me)) )
        {
                if( query("special_skill/sophistry", me) )
                {
                       if (quest_count >= 5000)
                               quest_count = 0;
                } else {
                       if (quest_count >= 2000)
                               quest_count = 0;
                }
        }
       else
        {
#endif
       if (quest_count >= 1000)
           quest_count = 0;
#ifdef DB_SAVE
        }
#endif
   } else
       if ((total_count % 10) == 0)
   {
       msg = "$N΢΢��ͷ�����ɵĲ�����Ȼ����"+chinese_number(quest_count)+
       "�ζ�û��ʧ�֣�������������ɣ���\n";
   }

   set("questsn_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_sn", me);

   //��¼�������Ĵ�������Ҫ���������������1000����������Ƭ
   all_quest_sn=query("all_quest_sn", me);
   if (!all_quest_sn) all_quest_sn = 0;
   all_quest_sn += 1;
   if (all_quest_sn == 1000)
   {
       obj = new("/clone/tessera/gem.c");
       tell_object(me,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                   "�и�"+query("name", obj)+"���ͽ������ˣ�\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_sn", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_sn", all_quest_sn, me);

   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_sn", me) )
    {
    if( (query("character", me) != "���ռ�թ") && (query("character", me) != "�ĺ�����") && !(query("shen", me)>0) )
        return 1;
    }
    */
    if( (quest=query("quest_sn", me)) )
    {
        message_vision("$Nί���ĵ��Ϻ�������ǰ���ߣ������������û����ɣ������������˼ҵ�����......��\n",me);
        /*
        if (quest["type"] == "��")
        {
                message_vision("$N����üͷ��$n˵���������Ǵ�һ������ô������ô�ѣ���ȥ��ϸ���룬�������һ��Ҫ��ɣ�\n",this_object(),me);
                return 1;
        }
        */
        if (quest["type"] == "��")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        if ( stringp(quest["maze"]) )
        {
            //MAZE_D->remove_maze(quest["maze"]);
            FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        message_vision("�Ϻ������$N΢Ц��˵:��û��ϵ���´κú�Ŭ������������\n", me);

        if (quest["type"] == "��")
        {
                delete("quest_sn", me);
                return 1;
        }
        set("questsn_times", 0, me);

        giveup=query_temp("sn_giveup", me);
        if ( giveup < 1 )
            set_temp("sn_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("sn_giveup", giveup+1, me);
        else set_temp("sn_giveup", 5, me);

        set("questsn_giveup_time", time(), me);

        delete("quest_sn", me);
    }
    else
        write("�Ϻ�����΢Ц�Ÿ����㣺����Ŀǰû���κ����񡣡�\n");
    return 1;
}

string time_period(int timep)
{
    int t, d, h, m, s;
    string time;
    t = timep;
    s = t % 60;             t /= 60;
    m = t % 60;             t /= 60;
    h = t % 24;             t /= 24;
    d = t;

    if(d) time = chinese_number(d) + "��";
    else time = "";

    if(h) time += chinese_number(h) + "Сʱ";
    if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";
    return time;
}

void destory(object ob)
{
    if(!ob) return;
    if(ob->is_character())
        message_vision("$NͻȻһ���̵��ܵ�ûӰ�ˡ�\n",ob);
    ob->move("/d/wizard/prison");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "�̺��岨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/bo",
                           "name"    : "�̺��岨",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "�ຣ�ޱ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/hai",
                           "name"    : "�ຣ�ޱ�",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "���ɾ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/jue",
                           "name"    : "���ɾ�",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "¾�ɾ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/lu",
                           "name"    : "¾�ɾ�",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/mie",
                           "name"    : "��������",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "�Ϻ���Ӱ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/nan",
                           "name"    : "�Ϻ���Ӱ��",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "staff"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "����������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/xuan",
                           "name"    : "����������",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "ն�ɾ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhan",
                           "name"    : "ն�ɾ�",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "���ɾ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhu",
                           "name"    : "���ɾ�",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
