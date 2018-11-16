// huang ����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "ȭ�Ź���" NOR
#define MY_OPINION      "unarmed"

#define QUEST_HS_D(x)   ("/quest/quesths/quest/quesths" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define HSMSG_D         ("/quest/quesths/quest/huangshang-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
mixed ask_skill();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string  *my_opinions = ({ "unarmed", "finger",
                          "strike", "cuff", "hand", "claw" });

string* hs_msg = ({
        "����ͷҲ��̧��˵����",
        "���ѷ���һ������������",
        "���ѵ�ͷ�����룬˵������",
        "��������һ�ݹ��ģ�˵������",
        "����΢΢Ц��Ц������",
});

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void create()
{
        set_name("����", ({ "huang shang", "huang" }) );
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 92);
        set("long", "�����������ţ��������书�ߵ͡�\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 32);
        set("int", 39);
        set("con", 37);
        set("dex", 32);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "�����澭" : "�벻������������д��һ����ѧ�ĵþ���ΪΣ�������Ĳ���֮�",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "��ѧ����(martial-cognize)�����ң���̸ʲô�书�أ�",
                "���Ĵ�" : (: ask_skill :),
                "����"     : "���Ժã����Ǹ���Ļ���������������������(quest)��\n",
                "�Թ�"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "ĳ��");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/dali/lushui");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "΢΢һЦ����$n"
                               CYN "���˵�ͷ��\n" NOR,
                               this_object(), me);
        }
        if( !is_fighting() &&random(5)==0)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("quest_hs", ob) && query("shen", ob)<0 )
                write("����˵����"+query("name", ob)+",���������ɵ���ô���ˣ�\n");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_hs", me);

        if (!quest)
                return "�㲢û�н��ҵ�����Ϲ����ʲô��";

        if ( undefinedp(quest["maze"]) )
                return "��ӵ�������Թ��޹أ��úð�����ͷ���������ˣ�";

        /* ȡ���ϵ��Թ�
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "����û�ã��Ǹ��Թ���˵���Ѿ���ʧ�ˣ�";

        message_vision("$N��$n��ͷ��������Ȼ���Ѿ�׼����Ҫȥ������м�һ��Ҫ�ɹ�����\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "�Ǻǣ�������书��̸ʲô���ۣ�";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "��������ȭ�ŷ������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�����Ҫ��Ҫ�����У�";

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

                message_vision(CYN "$N" CYN "���ڳ�˼��û�лش�$n"
                               CYN "��ֻ�ǰ��˰��֡�\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/huang", me) )
        {
        case 0:
                command("look"+query("id", me));
                command("say �ðɣ�����ֹ���һ�У��ҿ������ˮƽ��Ρ�");
                break;
        case 1:
                command("say ����˵������һ���ҿ�����");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ���ұ�������죡");
                return 1;
        }

        addn_temp("want_opinion/huang", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        action = SKILL_D(sp)->query_action(me, 0);
        if (mapp(action))
                lvl += (action["force"] + action["attack"] +
                        action["parry"] + action["dodge"] - 150) / 15;
        return lvl;
}

void do_congration(object me)
{
        command("chat ��ϲ��λ" + RANK_D->query_respect(me) + "��������"
                "������ֹ������������Ŭ������");
}

int accept_hit(object me)
{
        if( query_temp("want_hit/huang", me) >= 2 )
        {
                command("heng");
                command("say �²���������Ҫ�����Ǿ�ȥ���ɣ�");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say ��λ" + RANK_D->query_respect(me) + "��"
                "����֮���м�óȻ���ơ�");
        addn_temp("want_hit/huang", 1, me);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "��ϲ����$n" CYN
                               "�������ܺã������һ�û�к���"
                               "ʦ���ֹ����У����ɣ���\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/huang", me) )
        {
                command("say ƽ���޹ʶ�ʲô�֣�");
                return 0;
        }

        if( objectp(weapon=query_temp("weapon", me)) )
        {
                command("say �������е�" + weapon->name() + NOR +
                        CYN "���ҷ��£�" NOR);
                return 0;
        }

        if( query("qi", me)*100/query("max_qi", me)<80 || 
            query("jing", me)*100/query("max_jing", me)<80 )
        {
                command("say ������״̬���ѣ�����Ϣ������˵�ɣ�");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), 0);
        COMBAT_D->do_attack(this_object(), me, 0);

        if( query("qi", me) <= 0 )
        {
                message_vision(CYN "\n$N" CYN "ҡҡͷ��$n" CYN
                               "�����������ڵ��书�����Զ����"
                               "��һ�ж��Ӳ�ס����\n" NOR,
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision(CYN "\n$N" CYN "���ͷ���������ˣ����ȵ�"
                       "������������롣��\n" NOR,
                       this_object(), me);
        return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision(CYN "$N" CYN "��ŭ����������С����"
                               "ʲô�ң����ҹ�����˵��һ�ư�$n" CYN
                               "�����ڵء�\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "��������" && 
            query("character", me) != "��ʿ��˫" )
        {
                command("say ���ɷ����������ƶ�����һ��Ҫ��"
                        "�����䣬�����Բ��������ˡ�");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵľ����񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "jiuyin-shengong")
                return 1;

        if( query_temp("can_learn/huang/jiuyin-shengong", me) )
                return 1;


        set_temp("can_learn/huang/jiuyin-shengong", 1, me);
        command("nod");
        command("say �ܺã��Ҿʹ�������񹦰ɣ��ɲ�Ҫ��������"
                "�ĸ�����");
        return 1;

        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
        command("chat �գ��գ��գ��Ϸ�ȥҲ��");
        destruct(this_object());
        */
        full_self();
        return;
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/jiuyin-shengong/xin", me) )
        {
             command("say �㲻���Ѿ�������");
             return 1;
        }

        if( !query("can_learn/jiuyin-shengong/xin", me) )
        {
               message_sort(HIM "\n����̾����������������д��һ����ѧ�ĵã���Ի�������澭��������"
                            "��������о���ѧ֮�ã����Ͼ���ΪΣ�������Ĳ���֮���������ܽ����ϡ�"
                            "�������ռ��뽻�����ң��ұ㴫����С����Ĵ󷨡���\n", me);
               command("tan");

               return "����������Σ�";
        }


        if (me->query_skill("jiuyin-shengong", 1) < 240)
        {
               command("say ������񹦻�򻹲������һ����ܴ������У�");
               return 1;
        }
        if (me->query_skill("martial-cognize", 1) < 240)
        {
               command("say ����ѧ�������㣬������ȥ��ĥ��һ�°ɣ�");
               return 1;
        }
        if( !query("can_perform/jiuyin-shengong/shou", me )
            || !query("can_perform/jiuyin-shengong/zhi", me )
            || !query("can_perform/jiuyin-shengong/zhua", me )
            || !query("can_perform/jiuyin-shengong/zhang", me) )
        {
               command("shake");
               command("say ���㽫��������������������������Ұɣ�");
               return 1;
        }

        command("nod");
        command("say �ܺã��ܺã�");
        command("say ��Ȼ�����Ҿʹ������Ĵ󷨣�");
        message_sort(HIC "\n���ѽ�$N" HIC "�������ԣ�����$N" HIC "����С���ֹ��˼��䡣"
                       "���Ѳ�ʱ������������ֵı��飬$N" HIC "�����߿������ã�$N" HIC
                       "һ����Х���������Ƕ�Ȼ��ʧ���������� ����\n", me);
        command("haha");

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jiuyin-shengong"))
                me->improve_skill("jiuyin-shengong", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        tell_object(me, HIG "��ѧ���ˡ����Ĵ󷨡���\n" NOR);
        set("can_perform/jiuyin-shengong/xin", 1, me);
        return 1;
}
void die()
{
        /*
        message("vision", "\n"HIR + name() + "���һ����������һ����"
                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
        command("chat �Ϸ�ȥҲ��");
        destruct(this_object());
        */
        full_self();
        return;
}
/*
int accept_object(object me, object ob)
{
        if (base_name(ob) != "/clone/lonely/book/zhenjing1"
          && base_name(ob) != "/clone/lonely/book/zhenjing2")
        {
               command("say ��������ֶ�����ʲô��");
               return 0;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing1")
        {
               command("nod");
               command("say �ܺã��ܺã�");
               if( query("give_zhenjing2", me) )
               {
                     command("haha");
                     command("say ��Ȼ�����Ҿʹ�����У��������ʱ�����ң�");
                     tell_object(me, HIG "���Ѿ������㡸���Ĵ󷨡���\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing1", 1, me);
               command("say ����һ���������澭�²᡹���㾡���ҵ��������ң�");
               destruct(ob);
               return 1;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing2")
        {
               command("nod");
               command("say �ܺã��ܺã�");
               if( query("give_zhenjing1", me) )
               {
                     command("haha");
                     command("say ��Ȼ�����Ҿʹ�����У��������ʱ�����ң�");
                     tell_object(me, HIG "���Ѿ������㡸���Ĵ󷨡���\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing2", 1, me);
               command("say ����һ���������澭�ϲ᡹���㾡���ҵ��������ң�");
               destruct(ob);
               return 1;
        }

}
*/

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc;
    int i, giveup,tag,want,lev,lev1;
    int exp;
    int all_lvl,lvl;
    string msg,*sname,place;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "��������") && 
            (query("character", me) != "��ʿ��˫") && 
           (query("character", me) != "������") )
    {
        write("�������㣺�������Ը���ˣ��������ʲô��\n");
        return 1;
    }
    /*
    if( !(query("shen", me)<0) )
    {
        write("���ѿ�����ֻ��ҡͷ�������߽��������ǹ��������������ҽ��������ɱֹɱ����ɱ�Բ������������˰ɣ���\n");
        return 1;
    }
    */
    if (exp < 500000)
    {
        write("���Ѷ���˵�����������ڵľ��飬����Ҫ���ĥ������\n");
        return 1;
    }

    if( quest=query("quest_hs", me) )
    {
        write("���Ѷ���˵���Ȱ������ϵ����������˵��\n");
        return 1;
    }
    if( mapp(query("quest_dg", me)) )
    {
        write("���Ѷ���˵��������ܵ������㻹û��ɣ�Ī�������Ϸ��ִ�\n");
        return 1;
    }

    giveup=query_temp("hs_giveup", me);
    if( (time()-query("quesths_giveup_time", me))<20+giveup*2 )
    {
        write("���Ѷ������һ�����������겻�������Ҷ���ı��ֺܲ����⣬�ȷ�ʡһ�����\n");
        return 1;
    }

/*
        if( query("quesths_times", me)<3
         || (query("quesths_times", me)>5 && random(20) == 5) )
        {
                X_QuestD->query_quest(me, this_object());
                return 1;
        }
*/
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

    i=query("quesths_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"����΢΢Ц�ţ������˵������������������\n"+
              msg+"\n"+
              "���뷨Ūһ��"+qgood["name"]+"������ԼҪ "+want+" "+qgood["unit"]+"���ж��ٿ����Ƚ����١�ȥ�գ���\n"NOR;
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
        set("quest_hs", quest, me);
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
            /*
            NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"����һ��","����ɽ","����","����"}):
                                  query("combat_exp", me)<800000?({"����һ��","����ɽ","����"}):({"����һ��","����"}));
            */
            npc->set_from_me(me,1);
            addn_temp("apply/attack", npc->query_skill("force")/3, npc);
            addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
            addn_temp("apply/parry", npc->query_skill("force")/3, npc);
            addn_temp("apply/damage", 200+random(100), npc);
            addn_temp("apply/unarmed_damage", 200+random(100), npc);
            addn_temp("apply/armor", 200+random(300), npc);
            set_temp("quester",query("id",  me), npc);
            set("auto_perform", 1, npc);
            /*
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            */
            place=query("place", npc);

            set("shen",query("combat_exp",  npc)/2000, npc);
            msg="�������������˵����"+npc->name(1)+
                "������ʼ�����޳�֮ͽ���Σ�����֣���˵����������Թ��У���ȥ�������ɣ���\n";

            quest = ([
                //"maze" : maze_target->query("maze/mazename"),
                "maze" : maze_object,
                "name" : npc->name(1),
                "id":query("id", npc),
                "bonus": (200+random(51)),
                "type" :"ɱ",
                "level":8,
                //"chinese_w":place,
                //"where":npc->query("startroom"),
                "where": maze_target,
                "msg":msg,
                "object":base_name(npc),
            ]);
            tell_object(me,quest["msg"]+"\n");
            set("quest_hs", quest, me);

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
                quest = QUEST_HS_D(lvl)->query_quesths();
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
        case "ɱ":
                msg=HSMSG_D->query_hsmsg("ɱ",quest["name"]);
                break;
        case "Ѱ":
                msg=HSMSG_D->query_hsmsg("Ѱ",quest["name"]);
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/hs_target.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"����һ��","����ɽ","����","����"}):
                                      query("combat_exp", me)<800000?({"����һ��","����ɽ","����"}):({"����һ��","����"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                msg = hs_msg[random(5)]+npc->name(1)+"ȥ�������ͬ��������߲���Ǯ���ط��ֶ���ֶ�β��ã�"
                        "��˵�����������Թ��У���ȥ���ԣ�\n���Ҳ�ղ���Ǯ������������"+quest["name"]+"����������Ҫ��ʾ(chushi)һ�¡�";
                thing = new("/quest/quesths/wulin-ling");
                thing->move(me);
                message_vision("���ѽ��������$N��\n",me);
                quest["target"]=query("id", npc);
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/hs_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"����һ��","����ɽ","����","����"}):
                                      query("combat_exp", me)<800000?({"����һ��","����ɽ","����"}):({"����һ��","����"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = hs_msg[random(5)]+"����ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                        "�����������Թ��У�����ʱ�������ܾ��뿪�ˡ�";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("���ѽ�$N���ڵ��ϡ�\n",thing);
                } else message_vision("���ѽ�$N����$n��\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                break;
    }
    }
    quest["msg"] = msg;
    quest["level"] = tag;
/*
    if (quest["type"] == "ɱ" && random(6) == 3)
    {
        robot_quest = ([]);
        robot_quest = ANTI_ROBOT->get_question();
        msg = "";
        msg += "����֣��˵�������Ҹս�����ͬ�˵Ŀ��������һ�£���ȥ֪ͨһ��" + quest["name"] + NOR"���¿����ǣ�\n";
        set_temp("test", robot_quest, me);
        msg += robot_quest["question"];
        msg += "��ֻ��Ҫ��������"HIR"��ͨ��������ʽ"NOR"���͹�ȥ�����ˣ����͵�ָ���ǣ�whisper��\n";
        quest["type"]   = "��";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    if (maze_object)
        quest["maze"] = maze_object;

    set("quest_hs", quest, me);
    write(msg + "\n");
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times,i,tag,all_quest_hs,bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "��������") && (query("character", me) != "������") && query("character", me) != "��ʿ��˫" && !(query("shen", me)<0) )
    {
        write("��������������Ǻ��ˣ���\n");
        return 0;
    }
    else if( !(quest=query("quest_hs", me)) )
    {
        write("����˵�������޹�����»���������ջء���\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
                if (ob->value() < 1000000)
           {
                   tell_object(me,"�����������õĶ���˵����ôһ���Ǯ����������ʲô�����Լ����������ðɣ�\n");
                   return notify_fail("����̧ͷ���죬����˵�����������100���ƽ𣬻����Ҿ��������������\n");
           }
           delete("quest_hs", me);
           tell_object(me,"���ѽӹ����" + ob->name(1) + "��΢΢Ц��Ц����ͷ����������������������˰ɡ�\n");
           destruct(ob);
           return 1;
    }

    if (quest["type"]!="Ѱ"&&quest["type"]!="��"&&quest["type"]!="��"&&quest["type"]!="��")
    {
        write("����˵��������û�н���ȥ�Ҷ������������ջء���\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("���Ѵ�ŭ�����������С�ӣ���Ȼ����ƭ�����������ˣ���������ץ��������\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(��������)����%s(%s)(%s)����\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "��" )
    {
        if( query_temp("zheng", ob) != query("id", me) )
        {
            write("���ѽӹ�����һ��ŭ������������������ģ�������ƭ���������ߣ���Ľ������������ˣ���\n");
            addn("weiwang", -weiwang*(random(5)+4)/4, me);
            if( query("weiwang", me)<0)set("weiwang", 0, me);
            return 0;
        }
    } else if ( quest["type"] == "��" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("���ѽӹ���һ������Ȼ��ŭ���������Ż�ִ��˭����ģ���������Ū�ң���\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("���ѽӹ���һ������Ȼ��ŭ���������Ż�ִ�����Լ��õ���ô����������Ū�ң���\n");
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
                    write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
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
                    write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("����˵�������ⲻ������Ҫ�ġ���\n");
        return 0;
    }

//    message_vision("$N��$n�������ѡ�\n",me,ob);��give��Ϣ�ظ�haiyan
    times=query("quesths_times", me);//��������
    tag=query("quest_hs/level", me)+1;//����ȼ�
    if( (i=query("quesths_times", me))<15)i=15-i;
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
            addn("quest_hs/ok", 1, me);
            write("���ѽӹ������ͷ˵������ "+quest["ok"]+" �ˣ��ܺã����� "+(quest["want"]-quest["ok"])+" ��������Ŭ������\n");
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            score /= 3;
            GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_hs/all_bonus", exp, me);
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
    write("���ѽӹ���˵�������ܺã������������ɵò�����\n");
    destruct(ob);

    if (quest["type"]=="��" && objectp(obj = present("wulin ling", me)))
        destruct(obj);

    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"Ȼ��ȡ��һ���ƽ���㣺����ν���Щ���ӣ��´μ���Ŭ������\n"
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
        set("quesths_times", 1, me);
    else
        addn("quesths_times", 1, me);
    */
        set_temp("hs_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("quesths_times", me)+1;
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
        }
        else
        {
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
       msg = "$N΢΢��ͷ�����ɵĲ�����Ȼ����" +
       chinese_number(quest_count) +
       "�ζ�û��ʧ�֣�������������ɣ���\n";
   }

   set("quesths_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_hs", me);

   //��¼�������Ĵ�������Ҫ���������������1000������ˮ����Ƭ
   all_quest_hs=query("all_quest_hs", me);
   if (!all_quest_hs) all_quest_hs = 0;
   all_quest_hs += 1;
   if (all_quest_hs == 1000)
   {
       obj = new("/clone/tessera/gem.c");
       tell_object(me,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                   "�и�"+query("name", obj)+"���ͽ������ˣ�\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_hs", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D ->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_hs", all_quest_hs, me);
   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_hs", me) )
    {
    if( (query("character", me) != "��������") && (query("character", me) != "������") && !(query("shen", me)<0) )
        return 1;
    }
    */
    if( (quest=query("quest_hs", me)) )
    {
        message_vision("$Nսս�������ߵ�������ǰ�����С�ĸ���������������������......��\n",me);
        /*
        if (quest["type"] == "��")
        {
                message_vision("$N����üͷ��$n˵���������Ǵ�һ������ô������ô�ѣ���ȥ��ϸ���룬�������һ��Ҫ��ɣ�\n",this_object(),me);
                return 1;
        }
        */
        if ( stringp(quest["maze"]) )
        {
                //MAZE_D->remove_maze(quest["maze"]);
                FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        if (quest["type"] == "��")
        {
               if (ob = present("wulin ling",me))
               {
                        ob->move("/d/register/prison");
                        destruct(ob);
               }
        }
        if (quest["type"] == "��")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("���Ѷ�$N̾��һ����: ��ô�������Խ��ô�򵥵����鶼�����ˡ�\n", me);

        if (quest["type"] == "��")
        {
                delete("quest_hs", me);
                return 1;
        }
        rank=query("quest_hs/level", me);
        addn("weiwang", -(rank*6+random(rank+4)), me);
        if( query("weiwang", me)<0 )
               set("weiwang", 0, me);
        write("���Ѹ����㣺����Ľ������������ˣ���\n");

        set("quesths_times", 0, me);

        giveup=query_temp("hs_giveup", me);
        if ( giveup < 1 )
            set_temp("hs_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("hs_giveup", giveup+1, me);
        else set_temp("hs_giveup", 5, me);

        set("quesths_giveup_time", time(), me);

        delete("quest_hs", me);
    }
    else
        write("���Ѹ����㣺��Ŀǰû���κ�����\n");
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
    ob->move("/d/wizard/wizard_room");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "������ȭ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/quan",
                           "name"    : "������ȭ",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "cuff"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/shou",
                           "name"    : "��������",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "hand"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "���Ĵ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/xin",
                           "name"    : "���Ĵ�",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhang",
                           "name"    : "��������",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "������ָ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhi",
                           "name"    : "������ָ",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "������צ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhua",
                           "name"    : "������צ",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "claw"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
