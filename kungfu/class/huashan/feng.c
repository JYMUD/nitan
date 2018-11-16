// This program is a part of NITAN MudLIB
// feng.c ������

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

string ask_skill();
string ask_skill1();
string ask_skill2();
string ask_skill3();
mapping po_type = ([ "�ƽ�ʽ" : ({ "sword" }),
                     "�Ƶ�ʽ" : ({ "blade" }),
                     "��ǹʽ" : ({ "staff" }),
                     "�Ʊ�ʽ" : ({ "hammer", "club", "dagger" }),
                     "����ʽ" : ({ "whip" }),
                     "����ʽ" : ({ "unarmed", "finger", "claw",
                                   "strike", "hand", "cuff" }),
                     "�Ƽ�ʽ" : ({ "throwing" }),
                     "����ʽ" : ({ "force" }), ]);

int check_skill(string skill);
mixed teach_lonely_sword();

void create()
{
        set_name("������", ({ "feng qingyang", "feng", "qingyang" }));
        set("title", "��ɽ���ڳ���");
        set("nickname", HIW "��������" NOR);
        set("long", @LONG
����ǵ������𽭺��Ļ�ɽ���޷��������
�����ۣ��������������ֽ������ݳ���ü��
��һֱ������һ�ɵ�����������ɫ����Ȼ�Ե�
��Ľ���֮��һֱ����������
LONG);
        set("gender", "����");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 700);
        set_skill("zixia-shengong", 700);
        set_skill("huashan-neigong", 700);
        set_skill("dodge", 700);
        set_skill("feiyan-huixiang", 700);
        set_skill("huashan-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("huashan-sword", 700);
        set_skill("lonely-sword", 700);
        set_skill("blade", 700);
        set_skill("fanliangyi-dao", 700);
        set_skill("strike", 700);
        set_skill("hunyuan-zhang", 700);
        set_skill("cuff", 700);
        set_skill("poyu-quan", 700);
        set_skill("huashan-quan", 700);
        set_skill("huashan-zhang", 700);
        set_skill("literate", 700);
        set_skill("martial-cognize", 700);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        //create_family("��ɽ����", 0, "����");
        create_family("��ɽ��", 0, "����");

        set("inquiry", ([
                "����"    : (: ask_skill :),
                "Ц�׺�"  : (: ask_skill1 :),
                "����"    : (: ask_skill2 :),
                "����ͨ��": (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "sword.yi" :),
                (: perform_action, "sword.poqi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("can_perform/lonely-sword", ({ "sword", "blade", "staff",
                                           "hammer", "club", "dagger",
                                           "whip", "unarmed", "finger",
                                           "claw", "strike", "hand",
                                           "cuff", "force", "throwing" }));

        set("no_teach", ([
                "lonely-sword" : (: teach_lonely_sword :),
        ]));
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object ob, me = this_object();

        ::init();

        if (! objectp(me)) return;
        if (file_name(environment(me)) == "/d/huashan/xiaofang")
        {
                if (interactive(ob = this_player()) && ! ob->is_fighting()
                 && sizeof(query_temp("win", ob)) != 6
                &&  ! wizardp(ob))
                {
                        remove_call_out("auto_kill");
                        call_out("auto_kill", 1, ob );
                }else if( !query("see_feng", ob) )
                {
                        remove_call_out("improve_sword");
                        call_out("improve_sword", 1, ob );
                }
        }
}

int auto_kill(object ob)
{
        object me = this_object();

        command("say �üһﾹ��ı���ҹ����ɣ��������ɣ�");
        me->kill_ob(ob);
        ob->fight(me);
        return 1;
}

int improve_sword(object ob)
{
        int my_sword, add_level;

        if (! objectp(ob)) return 1;
        my_sword = ob->query_skill("sword", 1);
        command("say " + RANK_D->query_respect(ob) + "��Ȼһ�����������ҿ�ν��Ե������ָ����һЩ�����ɡ�");
        message_vision("�����￪ʼΪ$N��˵���������ľ��塣\n", ob);

        if (my_sword < 100)
        {
                add_level = my_sword + 20;
                tell_object( ob, "��Ļ������������˶�ʮ����\n");
        } else
        if (my_sword < 120)
        {
                add_level = my_sword + 10;
                tell_object( ob, "��Ļ�������������ʮ����\n");
        } else
        if (my_sword < 150)
        {
                add_level = my_sword + 5;
                tell_object( ob, "��Ļ��������������弶��\n");
        }
        else {
                message_vision("���������$N���ȵء���������һ����\n", ob);
                command("say " + RANK_D->query_respect(ob) + "�Ľ�����Ȼ�������ң����಻ʤ�����\n");
                tell_object(ob, "��Ļ��������ѳ�¯����֮������������ûʲô��ָ��������ˣ�\n");
                set("see_feng", 1, ob);
                return 1;
        }

        ob->set_skill("sword", add_level);
        set("see_feng", 1, ob);
        addn("combat_exp", 15000, ob);
        return 1;
}

mixed teach_lonely_sword()
{
        object me;

        me = this_player();

        if( query("family/family_name", me) != "��ɽ��"
             && query("family/family_name", me) != "��ɽ����" )
        {
                command("say �߿����ǻ�ɽ�ĵ�����һ�Ų��̡�");
                return -1;
        }

        if (me->query_skill("lonely-sword", 1) > 120)
        {
                if( query_temp("feng_has_told", me) )
                {
                        command("say ���Լ��ú����ɣ�");
                        return -1;
                }

                command("pat"+query("id", me));
                command("say ���׽���Ҫ���Լ��������Ժ����Լ�������аɣ�");
                set_temp("feng_has_told", 1, me);
                return -1;
        }

        if( query_temp("learnd_lonely_sword", me) )
                return 0;

        set_temp("learnd_lonely_sword", 1, me);
        command("say �ܺã��ܺá����Ž������ڽ��⣬������ʽ��");
        command("say ����ѧϰ���в��ɾ�������ʽ��");
        return 0;
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) != "��ɽ��"
             && query("family/family_name", ob) != "��ɽ����" )
        {
                command("say �߿����ǻ�ɽ�ĵ�����һ�Ų�����");
                return;
        }

        command("say �Ҳ���ͽ������������ɡ�");
}

int check_skill(string skill)
{
        if (skill != "sword" && skill != "lonely-sword")
        {
                command("say ��ֻ������������ѧ��ѧ������ѧ�����ˡ�");
                return -1;
        }
        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("can_learn/feng/lonely-sword", ob) )
                return check_skill(skill);

        if( query("can_learn/feng/sword", ob )
           && skill != "lonely-sword")
        {
                if (skill == "sword")
                        return 1;

                command("say �������������ǿ������㣬�ٸ������£�");
                return -1;
        }

        if( query_temp("have_asked_feng", ob) )
        {
                command("say ���������");
                return -1;
        }

        if( query("family/family_name", ob) != "��ɽ��"
             && query("family/family_name", ob) != "��ɽ����" )
        {
                command("say �߿����ǻ�ɽ�ĵ�����һ�Ų��̡�");
                return -1;
        }

        if( query("character", ob) == "���ռ�թ"
            || query("character", ob) == "�ĺ�����" )
        {
                command("heng");
                command("say �������ľ͸��ҹ���");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("character", ob) == "��������" )
        {
                command("hmm");
                command("say �����Բ���������ȴ���ʺ���ϰ���׽�����");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        /*
        if( query("shen", ob)<-10000
            || query("shen", ob)>10000
            || query("weiwang", ob)>10000 )
        {
                command("say �ҷ�ĳ�Ӳ��ͳ�����ʿ�򽻵������߰ɡ�");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }
        */

        if( query("int", ob)<26 )
        {
                command("sneer");
                command("say �������ͷ�죬߯���˵㣬�߰ɡ�");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("int", ob)<28 )
        {
                command("look "+query("id", ob));
                command("say �㵹�ǲ��㱿���е�С���������������ǲ��Զ����");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if (ob->query_skill("sword", 1) < 100)
        {
                command("say �����䲻��������ĶԽ��������Ҳδ��̫���ˡ�");
                return -1;
        }

        if( query("int", ob)<34 )
        {
                if (skill == "sword")
                {
                        command("say �ðɣ��Ҿͽ���һ����ڽ�����֪ʶ��");
                        set("can_learn/feng/sword", 1, ob);
                        return 1;
                }

                if (skill != "lonely-sword")
                {
                        command("say ��ֻ�ὣ����Ҫѧ�����ı����ұ��ʦ��ȥ�ɣ�");
                        return -1;
                }

                command("sigh");
                command("say ���������Ǵ�����������¾Ž����ǲ�֮��Զ��");
                return -1;
        }

        if (check_skill(skill) == -1)
                return -1;

        message_sort(HIW "\n$N" HIW "���˵�ͷ����$n" HIW "˵��������"
                     "�ã����á���Ȼ�Ҳ���ͽ��������������ʵ�ڲ���"
                     "�ʹ���һ�㽣���ɡ����׶��¾Ž�����Ϊ���ƣ�����"
                     "�����ܾ�ʽ�������ƽ�ʽ���Ƶ�ʽ����ǹʽ���Ʊ�ʽ"
                     "������ʽ������ʽ���Ƽ�ʽ������ʽ�����һһ�ֽ�"
                     "����������\n" NOR, this_object(), ob);

        tell_object(ob, HIC "\n������ͬ�⴫���㡸���¾Ž�����\n" NOR);
        set("can_learn/feng/lonely-sword", 1, ob);
        ob->improve_skill("martial-cognize", 1500000);
        return 1;
}

int accept_ask(object me, string topic)
{
        string *learned, *try_to;
        mixed pot;

        pot=query("potential", me);
        pot = atoi(pot);

        if (! topic || undefinedp(try_to = po_type[topic]))
                return 0;

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                command("say �����¾Ž�ô���������������");
                return 1;
        }

        learned=query("can_perform/dugu-jiujian", me);
        if (! arrayp(learned))
                learned = ({ });
        if (member_array(try_to[0], learned) != -1)
        {
                command("say �㲻���Ѿ�ѧ��" + topic + "��ô��");
                return 1;
        }

        command("say �ðɣ�" + topic + "��Ҫ����Ҫ����ϸ�ˡ�");
        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                tell_object(me, HIG "�����˷�����Ľ̵����ľ���ã����"
                                "����Ǳ�ܲ����ˡ�\n" NOR);
                return 1;
        }

        addn("learned_points", 10, me);
        if (random(2))
        {
                write(HIY "�����˷�����Ľ̵��������ĵá�\n" NOR);
                return 1;
        }

        learned -= try_to;
        learned += try_to;
        set("can_perform/dugu-jiujian", learned, me);
        tell_object(me, HIC "��ѧ���˶��¾Ž�֮��" + topic + "����\n");
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("lonely-sword"))
                me->improve_skill("lonely-sword", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        return 1;
}

string ask_skill()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "�����¾Ž�ô���������������";
        }

        if( query("can_perform/lonely-sword/pozhong", me) )
                return "�㲻���Ѿ�ѧ������";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"+
                HIG "�����˷�����Ľ̵����ľ���ã����"
                        "����Ǳ�ܲ����ˡ�" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"HIY "�����˷�����Ľ̵��������ĵá�" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/po",            //pfm�Ĵ���
                                        "name"          : "����",               //pfm������
                                        "sk1"           : "lonely-sword",       //��Ҫ���书��id
                                        "lv1"           : 80,                   //��Ҫ���书�ĵȼ�
                                        "sk2"           : "sword",              //��Ҫ�书sk2��id
                                        "lv2"           : 50,                   //��Ҫ�书sk2 �ĵȼ�
                                        "neili"         : 50,                   //��Ҫ�����ڹ�
                                        "free"          : 1,
                                        "gongxian"      : 300,
                                        ]));
}
string ask_skill1()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "�����¾Ž�ô���������������";
        }

        if( query("can_perform/lonely-sword/xiao", me) )
                return "�㲻���Ѿ�ѧ������";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"+
                HIG "�����˷�����Ľ̵����ľ���ã����"
                        "����Ǳ�ܲ����ˡ�" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"HIY "�����˷�����Ľ̵��������ĵá�" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/xiao",            //pfm�Ĵ���
                                        "name"          : "Ц�׺�",             //pfm������
                                        "sk1"           : "lonely-sword",       //��Ҫ���书��id
                                        "lv1"           : 180,                   //��Ҫ���书�ĵȼ�
                                        "sk2"           : "sword",              //��Ҫ�书sk2��id
                                        "lv2"           : 180,                   //��Ҫ�书sk2 �ĵȼ�
                                        "free"          : 1,
                                        "neili"         : 200,                   //��Ҫ�����ڹ�
                                        ]));
}

string ask_skill2()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "�����¾Ž�ô���������������";
        }

        if( query("can_perform/lonely-sword/hun", me) )
                return "�㲻���Ѿ�ѧ������";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"+
                HIG "�����˷�����Ľ̵����ľ���ã����"
                        "����Ǳ�ܲ����ˡ�" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"HIY "�����˷�����Ľ̵��������ĵá�" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/hun",            //pfm�Ĵ���
                                        "name"          : "����",             //pfm������
                                        "sk1"           : "lonely-sword",       //��Ҫ���书��id
                                        "lv1"           : 1000,                   //��Ҫ���书�ĵȼ�
                                        "sk2"           : "sword",              //��Ҫ�书sk2��id
                                        "lv2"           : 1000,                   //��Ҫ�书sk2 �ĵȼ�
                                        "neili"         : 2000,                   //��Ҫ�����ڹ�
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}

string ask_skill3()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "�����¾Ž�ô���������������";
        }

        if( query("can_perform/lonely-sword/jian", me) )
                return "�㲻���Ѿ�ѧ������";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"+
                HIG "�����˷�����Ľ̵����ľ���ã����"
                        "����Ǳ�ܲ����ˡ�" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "���¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵл��ȣ�������ʤ��\n"HIY "�����˷�����Ľ̵��������ĵá�" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/jian",            //pfm�Ĵ���
                                        "name"          : "����ͨ��",             //pfm������
                                        "sk1"           : "lonely-sword",       //��Ҫ���书��id
                                        "lv1"           : 1000,                   //��Ҫ���书�ĵȼ�
                                        "sk2"           : "sword",              //��Ҫ�书sk2��id
                                        "lv2"           : 1000,                   //��Ҫ�书sk2 �ĵȼ�
                                        "neili"         : 2000,                   //��Ҫ�����ڹ�
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}
