#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("�쵤��", ({ "zhu danchen", "zhu", "danchen" }));
        set("title", "���������" );
        set("nickname", CYN "������" NOR);
        set("long", "���Ǵ�����Ĵ���֮һ��һ������������Ĵ����ͷ��\n");
        set("gender", "����");
        set("age", 40);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1800);
        set("max_jing", 1000);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("duanshi-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("tiannan-bu", 120);
        set_skill("cuff", 120);
        set_skill("jinyu-quan", 120);
        set_skill("strike", 120);
        set_skill("wuluo-zhang", 120);
        set_skill("dagger", 140);
        set_skill("qingliang-daxuefa", 140);
        set_skill("parry", 120);
        set_skill("literate", 100000);
        set_skill("martial-cognize", 140);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("dagger", "qingliang-daxuefa");
        map_skill("parry", "qingliang-daxuefa");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                "͸�Ƕ�"   : (: ask_skill1 :),
        ]));

        create_family("���ϻ���", 15, "�ҳ�");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.ding" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
        add_money("silver", 10);
}

void init()
{
        ::init();
        add_action("do_learn","learn");
        add_action("do_learn","xue");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say ���ӵ��º�����ˣ�ֻҪ���·Ը�����һ�����ǡ�");
        command("say �����Ӳ������������ﵹ����һ�ױʷ����Դ������㡣");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "���ϻ���" )
        {
                command("sneer");
                command("say ��������ز���ʶ����֪���´˻��Ӻ�˵��");
                return -1;
        }

        if (skill != "qingliang-daxuefa" && skill != "dagger")
        {
                command("say ��ĳ��ƽֻ�Աʷ�һ�������о�������������֪��ǳ��");
                return -1;
        }

        if( !query_temp("can_learn/zhudanchen", ob) )
        {
                command("hehe");
                command("say ��Ȼ��������ϰ�䣬�������߾����ܴ��ڡ�");
                set_temp("can_learn/zhudanchen", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qingliang-daxuefa/ding", me) )
                return "�Ҳ����Ѿ��̸�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("qingliang-daxuefa", 1) < 1)
                return "������������Ѩ����δѧ����ô������һ˵��";

        if( query("family/gongji", me)<400 )
                return "ˡ����������ү�Ը��������ô������޹��ӵܡ�";

        if (me->query_skill("force") < 150)
                return "����ڹ���Ϊ̫�ѧ������һ�С�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ̫�ѧ������һ�С�";

        if (me->query_skill("qingliang-daxuefa", 1) < 100)
                return "��������Ѩ���Ļ�򻹲�������ȥ���������ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ�����ֽ�$N" HIY "�е���ǰ����"
                     "����$N" HIY "�����ֹ��˰��졣Ȼ���ְγ��������ȷ�ת��"
                     "�£�б�̶������ƺ���һ����Ϊ���صĴ�Ѩ����\n\n" NOR,
                     me, this_object());

        command("smile");
        command("say ���в��������������ӵ����Ժܿ�Ϳ������������ˡ�");
        tell_object(me, HIC "��ѧ���ˡ�͸�Ƕ�����\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("qingliang-daxuefa"))
                me->improve_skill("qingliang-daxuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingliang-daxuefa/ding", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

int accept_object(object who, object ob)
{
        int learn;

        learn=who->query_skill("literate",1);
        learn= learn?learn*10:500;

        if( !query("money_id", ob) )
                return 0;

        if( query("dushu", who) + 1 < 1 )
        {
                say(this_object()->name()+"Ц����������ô����˼�����ϴθ���Ǯ��û�����أ���\n");
                return 0;
        }

        if( ob->value()/15 + query("dushu", who) < 0 )
        {
                say(this_object()->name()+"�ܳ�������˵������ô��Ǯ�ҿɲ�����ѽ����\n");
                return 0;
        }

        if( !query("dushu", who) )
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"���˵�ͷ��˵����Ŷ�������������ĵ�ѧ�������ǲ�������ú�Ŭ��\n����������̶���д��(literate)���κ����⡣\n");
                        set("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"˵������ĳ��ⲻ������Ǯ�����û�ȥ�ɡ�\n");
                        return 0;
                }
        }
        else if(ob->value())
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"���˵�ͷ��˵����Ŷ�������������ĵ�ѧ�������ǲ�������ú�Ŭ�������ض�ǰ;������л�ˡ�\n");
                        addn("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"˵������ĳ��ⲻ������Ǯ�����û�ȥ�ɡ�\n");
                        return 0;
                }
        }
        return 1;
}

int do_learn(string arg)
{
        string skill, teacher;
        object me,ob,room;
        int learn,times,i;
        int master_skill, my_skill, gin_cost, my_combat_exp,grade;
        int t1,t2,t3,t4,lvl,neili_cost;
        string *args;
        int c, r, rand;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if(!arg || arg=="?" || arg=="/?")
                return notify_fail("ָ���ʽ��learn <ĳ��> [about] <����> <����>\n");

        /*
        if ((sscanf(arg, "%s about %s %d", teacher,skill,times)!=3 ))
        if ((sscanf(arg, "%s %s %d", teacher, skill,times)!=3 ))
                return notify_fail("ָ���ʽ��learn <ĳ��> [about] <����> <����>\n");
        */

        if( (i = sizeof(args = explode(arg, " "))) < 2 )
                return notify_fail("ָ���ʽ��learn|xue <ĳ��> <����> <����>\n");

        i--;
        if( i >= 2 && sscanf(args[i], "%d", times) && times )
                i--;
        else
                times = 1;
        skill = args[i--];
        if( args[i] == "about" && i >= 1 )
                i--;
        teacher = implode(args[0..i], " ");

        if (!ob->id(teacher))
                return 0;

        if( me->is_fighting() )
                return notify_fail("����ĥǹ������������\n");

        c = 200 + query_temp("apply/learn_times", me);
        if( present("learn emblem", me) )
                c += 1000;

        if( present("learn emblem2", me) )
                c += 1500;

        if( query("special_skill/wisdom", me) )
                c += 1000;

        if( times < 1 || times > c ) {
                write("ѧϰ��������һ�Σ����Ҳ���ܳ���" + chinese_number(c) +"�Ρ�\n");
                return 1;
        }

        if ((int)times<1) {
                write("��Ҫѧ���Σ�\n");
                return 1;
        }

        if( !living(ob) )
                return notify_fail("��....����Ȱ�" + ob->name() + "Ū����˵��\n");

        if (me->query_skill("literate",1) >=ob->query_skill("literate", 1) && query("dushu",me))
        {
                command("say ��...."+me->name()+"����ѧϰ���ù�������ֻ�ܽ��㵽���ˡ�������Ѿ����˿��Խ����ˡ�\n");
                return 1;
        }

        learn=me->query_skill("literate",1);

        if( !query("dushu", me) )
        {
                command("say �ף�"+me->name()+"���Ҳ��ǵ��չ������ѧ����....\n");
                return 1;
        }

        if( query("dushu", me)<times ) {
                command("say �ף�"+me->name()+"���㽻��Ǯ�Ѿ�����ѧ��ô����˰�....\n");
                return 1;
        }

        if (!learn)     learn=10;
        if (skill!="literate") {
                write("���������±����ұ���ѧ�ˡ�\n");
                return 1;
        }
        if (! room=find_object(query("startroom",ob)))
                room=load_object(query("startroom",ob));
        if (room!=environment()){
                command("say �ҳ�������£����һ�ȥ��˵�ɣ�");
                return 1;
        }
        /*
        if (ob->query("jing<30"))
        {
                 ob->set("env/no_teach",1);
                command("say �ҽ������ˣ���Ҫȥ��Ϣ�ˣ�");
                return 1;
        }
        */
        my_skill = me->query_skill(skill, 1);
        master_skill = ob->query_skill(skill, 1);
        if( my_skill >= master_skill ) {
                write("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");
                return 1;
        }

        if( (query("level", me) < 60 && my_skill > 10000) ||
            (query("level", me) < 80 && my_skill > 20000) ||
            (query("level", me) < 100 && my_skill > 30000) ) {
                write("�������ĳ̶��Ѿ��ﵽ�ⶥ�����ˡ�\n");
                return 1;
        }

        if( (query("potential", me) - query("learned_points",me)) < times )
                return notify_fail("���Ǳ�ܲ���ѧϰ��ô����ˡ�\n");

        gin_cost = 150 / (int)me->query_int() + 1;
        if( !my_skill ) {
                gin_cost *= 2;
                me->set_skill(skill,0);
        }
        printf("����%s����йء�%s�������ʡ�\n", ob->name(), to_chinese(skill));

        t1 = query("jing",me) / gin_cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  gin_cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( (int)query("neili",me) >= neili_cost * t2 ) {
                        t4 = times;
                        addn("neili", -neili_cost * t2, me);
                }
                else {
                        t3 = (int)query("neili",me) / neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                                write("Ȼ�������̫���ˣ��޷��ٽ����κ�ѧϰ�ˡ�\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", gin_cost * t1);
        else
                me->receive_damage("jing", gin_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        my_combat_exp = (int)query("combat_exp",me);
        if(my_combat_exp < 10000)
                grade = 1;
        else if(my_combat_exp < 80000)
                grade = 3;
        else if(my_combat_exp < 500000)
                grade = 7;
        else
                grade = 13;
        if ( grade < 1 )
                grade = 1;

        rand = 10 + random((int)me->query_int() - 9);
        if( my_skill >= 20000 ) rand /= 4;
        else if( my_skill >= 15000 ) rand /= 3;
        else if( my_skill >= 10000 ) rand /= 2;
        else if( my_skill >= 5000 ) rand = rand * 2 / 3;

        if( intp(r = query_temp("apply/learn_effect",me)) )
                rand += rand * r / 100;

        if( query("time_reward/study",me) )
                rand += rand * 50 / 100;

        if( query("special_skill/wisdom",me) )
                rand += rand * 50 / 100;

        printf("������%s��ָ�����ƺ���Щ�ĵá�\n", ob->name());
        addn("learned_points", t4, me);
        // me->improve_skill(skill, t4*grade * (10 + random((int)me->query_int() - 9)));
        me->improve_skill(skill, t4*grade*rand);

        if( t4 > 0 && t4 < times )
                write("���������̫���ˣ�ѧϰ��" + chinese_number(t4) +
                      "���Ժ�ֻ����ͣ������\n");

        addn("dushu", -t4, me);
        return 1;
}
