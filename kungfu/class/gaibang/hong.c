// This program is a part of NT MudLIB
// hong.c ���߹�

#include <ansi.h>;
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;
inherit F_NOCLONE;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();
mixed ask_skill12();
mixed ask_skill13();

mixed ask_me();

//#define YUZHU    "/clone/lonely/yuzhu"
#define YUZHU    "/clone/lonely/lvyuzhang"

int try_to_learn_ds();
int try_to_learn_db();

void create()
{
        object ob;
        set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
        set("long", @LONG
������ؤ���ʮ���ΰ������ųƾ�ָ��ؤ�ĺ�
�߹���ү�ӡ�ֻ������ü�԰ף�������������
���ѣ�ģ������������������Ŀ����磬�Ե�
������Ȼ����ŭ��������
��һ�ų����������΢�룬���ִ�ţ�������
����һ����һ��Ĵ����˲�����ȴϴ�øɸɾ�
����
LONG);

        set("nickname", HIW "��ؤ" NOR);
        set("gender", "����");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");

        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 6700);
        set("max_jing", 57000);
        set("neili", 77000);
        set("max_neili", 77000);
        set("jiali", 300);
        set("combat_exp", 6000000);
        set("level", 60);
        set("score", 600000);
        set("shen_type", 1);
        set("book_count", 5);

        set_skill("force", 700);             // �����ڹ�
        set_skill("array", 700);
        set_skill("dagou-zhen", 700);
        set_skill("huntian-qigong", 700);    // ��������
        set_skill("jiaohua-neigong", 700);
        set_skill("yijin-duangu", 700);      // �׽�͹�
        set_skill("unarmed", 750);
        set_skill("cuff", 750);
        set_skill("changquan", 750);
        set_skill("strike", 700);            // �����Ʒ�
        set_skill("dragon-strike", 700);     // ����ʮ����
        set_skill("hand", 700);              // �����ַ�
        set_skill("shexing-diaoshou", 700);  // ���е���
        set_skill("dodge", 700);             // ��������
        set_skill("feiyan-zoubi", 700);      // �����߱�
        set_skill("xiaoyaoyou", 700);        // ��ң����
        set_skill("parry", 700);             // �����м�
        set_skill("dagou-bang", 700);        // �򹷰���
        set_skill("jiaohua-bangfa", 700);
        set_skill("staff", 700);             // �����ȷ�
        set_skill("fengmo-zhang", 700);      // ��ħ�ȷ�
        set_skill("blade", 700);             // ��������
        set_skill("liuhe-dao", 700);         // ���ϵ�
        set_skill("throwing", 700);          // ��������
        set_skill("pomie-jinzhen", 700);     // �������
        set_skill("begging", 700);           // �л�����
        set_skill("checking", 700);          // ����;˵
        set_skill("training", 700);          // Ԧ����
        set_skill("literate", 700);          // ����д��
        set_skill("bixue-danxin", 700);
        set_skill("martial-cognize", 600);   // ��ѧ����
        /*
        set_skill("kanglong-youhui", 700);   // 1
        set_skill("feilong-zaitian", 700);   // 2
        set_skill("jianlong-zaitian", 700);  // 3
        set_skill("hongjian-yulu", 700);     // 4
        set_skill("qianlong-wuyong", 700);   // 5
        set_skill("lishe-dachuan", 700);     // 6
        set_skill("turu-qilai", 700);        // 7
        set_skill("zhenjing-baili", 700);    // 8
        set_skill("huoyue-zaiyuan", 700);    // 9
        set_skill("shuanglong-qushui", 700); // 10
        set_skill("yuyue-yuyuan", 700);      // 11
        set_skill("shicheng-liulong", 700);  // 12
        set_skill("miyun-buyu", 700);        // 13
        set_skill("sunze-youfu", 700);       // 14
        set_skill("longzhan-yuye", 700);     // 15
        set_skill("lvshuang-bingzhi", 700);  // 16
        set_skill("diyang-chufan", 700);     // 17
        set_skill("shenlong-baiwei", 700);   // 18
        */

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("cuff", "changquan");
        map_skill("hand",  "shexing-diaoshou");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("blade", "liuhe-dao");
        map_skill("throwing", "pomie-jinzhen");

        prepare_skill("strike", "dragon-strike");

        set("no_teach", ([
                "dragon-strike" : (: try_to_learn_ds :),
                "dagou-bang"    : (: try_to_learn_db :),
        ]));

        set("inquiry", ([
                "������"   : "�Ͻл���û�������ô�����£���ȥ������С��ɣ�\n",
                "������"   : "����������������\n",
                "ؤ��"     : "����������������\n",
                "С��"     : "����Ե����ض��յĽл�����ţ�����������������ײˣ���������������\n",
                "�óԵ�"   : "����Ե����ض��յĽл�����ţ�����������������ײˣ���������������\n",
                "����"     : "��С�����յĽл�����ţ�����������������ײˣ���������óԡ�\n",
                "�ض�"     : "��С�����յĽл�����ţ�����������������ײˣ���������óԡ�\n",
                "������"   : (: ask_me :),
                "���ξ�"   : (: ask_skill1 :),
                "������"   : (: ask_skill2 :),
                "���־�"   : (: ask_skill3 :),
                "���־�"   : (: ask_skill4 :),
                "���־�"   : (: ask_skill5 :),
                "���־�"   : (: ask_skill6 :),
                "�����޹�" : (: ask_skill7 :),
                "������"   : (: ask_skill8 :),
                "����һ��" : (: ask_skill9 :),
                "�������" : (: ask_skill10 :),
                "�����л�" : (: ask_skill11 :),
                "��ɽ����" : (: ask_skill12 :),
                "��Х����" : (: ask_skill13:),
        ]));

        set("chat_chance", 1);
        set("chat_msg", ({
                "���߹����Ŷ�Ƥ̾�����������þ�û�Ե��ض��յ�С���ˡ�����\n",
                "���߹������½���һ�ɣ���ʼ˯������˯���૵����������л����������㣡���㣡��\n",
                "���߹�˵�������׻�˵�����ڽ��ϡ��������Ͻл��ص��������ݿ�������\n",
                "���߹�ҡͷ̾������������С�л���ô���񶼲����ղ��ˣ���\n",
                "���߹��૵���������ؤ��ġ�����ʮ���ơ���������Ե����Ʒ�����\n",
        }));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xiang" :),
                (: perform_action, "strike.hui" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "dodge.xian" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.chuo" :),
                (: perform_action, "staff.feng" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "staff.tian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        create_family("ؤ��", 17, "����");
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        if (clonep())
        {
                ob = find_object(YUZHU);
                if (! ob) ob = load_object(YUZHU);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                }
        }
        //carry_object(__DIR__"obj/lvyv_bang")->wield();
        carry_object(__DIR__"obj/jiaohuaji");
        carry_object(__DIR__"obj/cloth")->wear();

        set("startroom", "/d/gaibang/gbxiaowu");
        check_clone();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("level", ob)<3 )
        {
                command("hmm");
                command("say ��ľ�����ô����ܸ���ѧʲô��");
                return;
        }

        if (ob->query_str() < 40 && ob->query_int() < 40
            && ob->query_con() < 40 && ob->query_dex() < 40)
        {
                command("say ��˵���������Ҳ���У��Խ�Ҳ����⣬���ܺ���ѧʲô��");
                return;
        }

        if ((int)ob->query_skill("force") < 180)
        {
                command("hmm");
                command("say ����ڹ����̫���ˣ��Ⱥú������������ҡ�");
                return;
        }

        if( query("max_neili", ob)<2000 )
        {
                command("hmm");
                command("say �����ǵ���������ѧ����ʲô�ϳ��书��");
                return;
        }
        command("say ����ƽʱ�ù�Ŭ���������Ͻл��������㡣");
        command("say �Ժ�ú��������ɱ���Ҷ�����");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/hong/dragon-strike", me )
             && !query("can_learn/hong/xiaoyaoyou", me) )
        {
                command("say ����˭���������ģ�Ҫ��ɶ��");
                return -1;
        }

        if( (query("can_learn/hong/dragon-strike", me )
            && skill != "dragon-strike"
            && skill != "strike")
             || (query("can_learn/hong/xiaoyaoyou", me )
            && skill != "xiaoyaoyou"
            && skill != "strike"))
        {
                command("say �Ͻл�����ʲô��ѧʲô���㲻ѧ�����ˡ�");
                return -1;
        }

        if (skill == "strike"
            && me->query_skill("strike", 1) > 379)
        {
                command("say ����Ϊֹ����Ĺ���Ҳ�����ˣ�ʣ�µ��Լ�ȥ����");
                return -1;
        }
        return 1;
}

int try_to_learn_db()
{
        object me;

        me = this_player();
        if( query("can_learn/hong/dagou-bang", me) )
                return 0;

        if( query("family/beggarlvl", me)<7 )
        {
                command("say Ҳ����������ʲô���֣���Ȼ��ѧ�򹷰�����");
                return -1;
        }

        if( query("shen", me)<80000 )
        {
                command("say ����������»����ò����������ȷ�����ʱ�����ܴ��㡣");
                return -1;
        }

        command("sigh");
        command("say ���״򹷰����������ഫ������ֻ���������ΰ���������ѧ��");
        command("say �������ڽ������ң���Ҳ���Ǳ�����֣�����ѧ֮�޷���");
        set("can_learn/hong/dagou-bang", 1, me);
        return 0;
}

int try_to_learn_ds()
{
        object me;
        object sob;
        int i;
        int flag;
        string *sub_skills;

        me = this_player();

        if( !query("can_learn/hong/dragon-strike", me) )
                return -1;

        if( query("family/family_name", me) != query("family/family_name") )
        {
                command("say �����봫���㽵��ʮ���ƣ�����ϧ�㲻����ؤ��ġ�");
                delete("can_learn/hong/dragon-strike", me);
                return -1;
        }

        if( query("family/family_name", me) == query("family/family_name" )
             && query("family/beggarlvl", me)<9 )
        {
                command("say ��Ҫѧ����ʮ���ƣ������������ﳤ����˵�ɣ�");
                return -1;
        }

        if( query("family/family_name", me) != query("family/family_name" )
             && !query("can_learn/hong/dragon-strike", me) )
        {
                command("say �����������ģ�һ�ߴ���ȥ��");
                return -1;
        }

        if( query("shen", me)<80000 )
        {
                command("say ����������»����ò������ҿɲ����Ĵ��������");
                return -1;
        }

        sob = find_object(SKILL_D("dragon-strike"));

        if (! sob)
        sob = load_object(SKILL_D("dragon-strike"));

        if (! sob->valid_learn(me))
                return 0;

        if (me->query_skill("dragon-strike", 1))
        {
                command("say �㲻���Ѿ�����ô���Լ��ú����ɡ�");
                return -1;
        }

        sub_skills = keys(sob->query_sub_skills());

        flag = 0;
        for (i = 0; i < sizeof(sub_skills); i++)
        {
                if (me->query_skill(sub_skills[i], 1) >= 10)
                        continue;

                me->set_skill(sub_skills[i], 10);

                if (! flag)
                {
                        flag = 1;
                        command("nod");
                        command("say �ҽ�ʮ��·�Ʒ��������㣬����ʱ"
                                "�գ������ڻ��ͨ��");
                }
                tell_object(me, HIC "���" + to_chinese(sub_skills[i]) + "����"
                            "һЩ����\n" NOR);
        }

        if (! flag)
        {
                command("say ����˵�˴������ڻ��ͨ���������ֽ���");
                return -1;
        }

        command("say ���Ƚ���ʮ��·�Ʒ��ڻ��ͨ���϶�Ϊһ��˵�ɡ�");
        notify_fail("���Լ���ȥ�ú���ϰ�ɡ�\n");
        return -1;
}

int accept_object(object who, object ob)
{
        int lv;
        string by;
        object me;
        string hid;
        object hob;
        int r;

        me = this_object();

        if (r = ::accept_object(who, ob))
                return r;

        if( !query("food_supply", ob) )
        {
                command("say �ⶫ������ȥҲûɶ�ر�ģ����Ը����Űɡ�");
                return -1;
        }

        if( !intp(lv=query("level", ob) )
            || lv < 1
             || !stringp(by=query("by", ob)) )
        {
                command("say �ⶫ������ȥҲûɶ�ر�ģ����Ը����Űɡ�");
                return -1;
        }

        if (lv < 100)
        {
                message_vision(CYN "$N" CYN "������" + ob->name() +
                               CYN "����ü�����ⶫ���㻹���Ը�����"
                               "�ɡ�\n" NOR, me);
                return -1;
        }

        if (lv < 120)
        {
                message_vision(CYN "$N" CYN "������" + ob->name() +
                               CYN "����ζ�������ɻ�����΢Ƿ��ô"
                               "������\n" NOR, me);
                return -1;
        }

        message_vision(HIW "$N" HIW "������$n" HIW "������" + ob->name() +
                       HIW "�����˼��ڣ�ֱ����ͷ���������ޡ�\n" NOR, me, who);

        if (! who->id(by))
        {
                command("say ��ϧ��֪����˭���ģ��пտɵø�������������");
                return 1;
        }

/*
        if( query("gender", who) != "Ů��" )
        {
                command("say �벻����һ������ү������Ҳ�����ѵã��ѵá�");
                return 1;
        }
*/

        if( query("family/family_name", who) != query("family/family_name") )
        {
                command("say ��ϧ�㲻�Ǳ�������ˣ����򵽿��Դ�����һЩ����");
                return 1;
        }

        if( query("can_learn/hong/xiaoyaoyou", who) >= 1 &&
            query("can_learn/hong/dragon-strike", who) >= 1 )
        {
                command("pat "+query("id", who));
                command("say �ָ��Ͻл�������ˣ���л����л��");
                return 1;
        }
        command("stuff");
        command("say �Ͻл�ûɶֵǮ�ģ��ʹ���һ��ȭ����Ϊ����ɡ�");

        tell_object(who, HIC "\n���߹�ͬ�⴫���㡸��ң��ȭ������\n" NOR);
        addn("can_learn/hong/xiaoyaoyou", 1, who);
        // who->improve_skill("martial-cognize", 1700000);

        // if (lv >= 200 && (string)ob->query("name") == "�л���")
        if (lv >= 200)
        {
                // message_vision("���߹��е�������������������ԵĽл���ѽ��\n",
                                // me, who);
                message_vision(CYN "\n$N" CYN "��˼���ã��ֵ����벻"
                               "�����˻�Ѿͷ����Ȼ�����������������"
                               "ζ��\n" NOR, me, who);

                hid=query("couple/couple_id", who);
                if( 1 )
                {
/*
                        if( query("family/family_name", who) != query("family/family_name") ||
                            !query("reborn", who) )
                        {
                                command("say ȴ��֪��������ż���û�У���Ҫ"
                                        "�Ͻл�������ܣ�");
                                return 1;
                        } else
*/
                        {
                                tell_object(who, HIC "\n���߹�ͬ�⴫���㡸����ʮ���ơ���\n" NOR);
                                addn("can_learn/hong/dragon-strike", 1, who);
                                who->improve_skill("martial-cognize", 1700000);
                                return 1;
                        }
                }

                if (! objectp(hob = find_player(hid)))
                {
                        command("sigh");
                        command("say ��ϧ����λ���ڣ������ҵ��ǿ���"
                                "�������ֹ��򡣰��ˣ����ˡ�");
                        return 1;
                }

                if( query("family/family_name", hob) != query("family/family_name") )
                {
                        command("say " + hob->name(1) + "��Ȣ������"
                                "�������ţ�Ҳ�����ˡ�");
                        return 1;
                }
                if( query("can_learn/hong/dragon-strike", hob) )
                {
                        command("say " + hob->name(1) + "�Ѿ����ˡ�����ʮ���ơ�����"
                                "��������ǰ׳��ˣ���л����л��");
                        return 1;
                }

                command("say ʲôʱ�����Ҳ������λ������Ҳ�����㶫����");

                tell_object(hob, HIC "\n���߹�ͬ�⴫���㡸����ʮ���ơ���\n" NOR);
                set("can_learn/hong/dragon-strike", 1, hob);
                hob->improve_skill("martial-cognize", 1700000);
        }
        destruct(ob);
        return 1;
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/xiaoyaoyou/xian", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
             && !query("can_learn/hong/xiaoyaoyou", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("xiaoyaoyou", 1) < 1)
                return "������ң��ȭ����ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
             && query("family/gongji", me)<300 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<10000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 120)
                return "����ڹ�����㣬����ȥ������������";

        if (me->query_skill("xiaoyaoyou", 1) < 100)
                return "�����ң��ȭ�����δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "���һ㶣��漴���ֽ�$N"
                     HIY "�е�����ǰ����$N" HIY "����������"
                     "����Щ����$N" HIY "���˰��죬ͻȻ�䲻"
                     "�ɻ��ĵ�һЦ��������������\n\n" NOR,
                     me, this_object());

        command("say �ھ����������ˣ��Լ���ȥ����ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����ξ�����\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1700000);
        if (me->can_improve_skill("xiaoyaoyou"))
                me->improve_skill("xiaoyaoyou", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/xiaoyaoyou/xian", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/pomie-jinzhen/du", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("pomie-jinzhen", 1) < 1)
                return "�������컨�궼ûѧ�������������У�";

        if( query("family/gongji", me)<500 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<10000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����㣬����ȥ������������";

        if (me->query_skill("pomie-jinzhen", 1) < 150)
                return "������컨����δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "����һЦ����$N" HIY "������ǰ����"
                     "����$N" HIY "�����ֹ��˰��졣�����������֣�ʮָ"
                     "���ţ�һ��һ������������һ�ֺ��ر�İ������š�\n"
                     "\n" NOR, me, this_object());

        command("say ���еľ�Ҫ���ǳ���Ѹ�ݣ����в������Ǻ��ˣ�");
        tell_object(me, HIC "��ѧ���ˡ������롹��\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1700000);
        if (me->can_improve_skill("pomie-jinzhen"))
                me->improve_skill("pomie-jinzhen", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/pomie-jinzhen/du", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill3()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/chan", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "�����򹷰�����ûѧ�������������У�";

        if( query("family/gongji", me)<300 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<80000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 100)
                return "����ڹ�����㣬��ȥ���ߵ�������";

        if (me->query_skill("dagou-bang", 1) < 60)
                return "��Ĵ򹷰������δ�����ٻ�ȥ������";

        message_sort(HIY "\n$n" HIY "����$N" HIY "һ�ۣ�������ü����"
                     "�����������ϵĳ��������������$N" HIY "�����ɻ�"
                     "�䣬ȴֻ����ǰһ����â���������ܽ���$n" HIY "��"
                     "���İ�Ӱ���ܶ����ѣ��ٱ����˸���æ���ҡ�\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say �򹷰���ʽ����ӯ�������ƣ������ⷽ��ö��¹���");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/chan", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill4()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/chuo", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "�����򹷰�����ûѧ�������������У�";

        if( query("family/gongji", me)<600 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<80000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 160)
                return "����ڹ�����㣬��ȥ���ߵ�������";

        if (me->query_skill("dagou-bang", 1) < 100)
                return "��Ĵ򹷰������δ�����ٻ�ȥ������";

        message_sort(HIY "\n$n" HIY "����һЦ����$N" HIY "������ǰ����"
                     "����$N" HIY "�����ֹ��˰��졣����ְγ����������"
                     "�������Բ�����͵�ֱ�̶�������������һ�ֺܾ����"
                     "�ȷ���ѧ��$N" HIY "һ����һ�߲�ס�ĵ�ͷ��\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say ���������Ƶвзϣ�ʹ��ʱ�ö�����⡣");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/chuo", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill5()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/feng", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "�����򹷰�����ûѧ�������������У�";

        if( query("family/gongji", me)<1700 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<80000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ�����㣬��ȥ���ߵ�������";

        if (me->query_skill("dagou-bang", 1) < 120)
                return "��Ĵ򹷰������δ�����ٻ�ȥ������";

        message_sort(HIY "\n$n" HIY "���һ㶣��漴���ֽ�$N"
                     HIY "�е�����ǰ����$N" HIY "����������"
                     "����Щ����$N" HIY "���˰��죬ͻȻ�䲻"
                     "�ɻ��ĵ�һЦ��������������\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say ��ǿʱʹ�������㵱�Ա�����ȥ���ٶ�������");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/feng", 1, me);
        addn("family/gongji", -1700, me);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/ban", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "�����򹷰�����ûѧ�������������У�";

        if( query("family/gongji", me)<1800 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<100000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 240)
                return "����ڹ�����㣬��ȥ���ߵ�������";

        if (me->query_skill("dagou-bang", 1) < 180)
                return "��Ĵ򹷰������δ�����ٻ�ȥ������";

        message_sort(HIY "\n$n" HIY "����$N" HIY "һ�ۣ�������ü����"
                     "�����������ϵĳ��������������$N" HIY "�����ɻ�"
                     "�䣬ȴֻ����ǰһ����â���������ܽ���$n" HIY "��"
                     "���İ�Ӱ���ܶ����ѣ��ٱ����˸���æ���ҡ�\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say ���еľ�Ҫ���ǳ�����ʤ������ȥ���Լ����ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/ban", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}
/*
mixed ask_skill7()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/tian", me) )
                return "�Լ�ȥ���ɣ��ϲ����Ҹ�ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��ɶ����ʲôʱ��˵��Ҫ���㣿";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "�����򹷰�����ûѧ�������������У�";

        if( query("family/gongji", me)<2000 )
                return "���ڰ���������Ϊ���������Ҵ������㣿��";

        if( query("shen", me)<100000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if( query("family/beggarlvl", me)<9 )
                return "���ڰ��еı��ֻ��������ȳ�Ϊ������˵�ɡ�";

        if( !query("can_perform/dagou-bang/chan", me )
            || !query("can_perform/dagou-bang/chuo", me )
            || !query("can_perform/dagou-bang/feng", me )
            || !query("can_perform/dagou-bang/ban", me) )
                return "��򹷰������ĸ��������˽�͸����ô��";

        if (me->query_skill("force") < 300)
                return "����ڹ�����㣬��ȥ���ߵ�������";

        if (me->query_skill("dagou-bang", 1) < 220)
                return "��Ĵ򹷰������δ�����ٻ�ȥ������";

        message_sort(HIY "\n$n" HIY "������$N" HIY "��һ�ᣬ����"
                     "���˵�ͷ�����ֳ��������ȣ����һ��������"
                     "�������������ǧ�ٸ����ƣ���������$N" HIY
                     "�����ھ���֮�У���ʽ���棬�����ױȣ�����̾"
                     "Ϊ��ֹ��\n\n" NOR, me, this_object());

        command("stuff");
        command("say �㵽������̶ȣ���Ҳûɶ�ý̵��ˣ��Լ������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������޹�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/tian", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}
*/
mixed ask_skill7()
{
        object me, obj;

        me = this_player();

        if( query("family/family_name", me) != query("family/family_name") )
                return "��һ��ȥ��";

        if (me->query_skill("dagou-bang", 1) < 250)
                return "��Ĵ򹷰���ѧ����ô�������ҿ������Զ�أ�";

        if (query("book_count") <1)
                return "�������ˣ��򹷰��ؼ����Ѿ����ȥ�ˡ�";
        obj = new(__DIR__"obj/book.c");
        set("master",query("id",  me), obj);
        obj->move(me);
        tell_object(me, "���߹�˵�������ðɣ��Ȿ�ؼ�����ȥ�ú��о��ɣ���\n");
        addn("book_count", -1);
        return 1;
}

mixed ask_skill8()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/qin", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && !query("can_learn/hong/dragon-strike", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<800 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 300)
                return "���ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "���˵�ͷ��ת��������$N" HIY "˵"
                     "�������Ҹ�����ʾһ�飬�����ˡ����������䣬����"
                     "$n" HIY "һ�����ȣ�ȫ���ھ��ŷ��������ұ۷�����"
                     "����һʱ����ֻ����Χ����ӿ�������ϳ���������$n"
                     HIY "������ӿȥ��\n\n" NOR, me, this_object());

        command("say ��ʽ������ˣ����Լ���ȥ����ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������֡���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/qin", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/lei", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && !query("can_learn/hong/dragon-strike", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<2000 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 300)
                return "���ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "���˵�ͷ��ת��������$N" HIY "˵"
                     "�������Ҹ�����ʾһ�飬�����ˡ����������䣬����"
                     "$n" HIY "һ�����ȣ�ȫ�������Ķ���˫����ɽ������"
                     "ѹ������ʱֻ�������ꡱһ�����죬$n" HIY "��ǰ��"
                     "����ڴֵ�����Ӧ��������ֱ����$N" HIY "Ŀ�ɿڴ�"
                     "������˵����������\n\n" NOR, me, this_object());

        command("sweat");
        command("say ��ʽ������ˣ����Լ���ȥ����ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����һ������\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/lei", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill10()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/xiang", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && !query("can_learn/hong/dragon-strike", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<3000 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force") < 300)
                return "���ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "��˼���ã����Ż������˵�ͷ����"
                     "�ֽ�$N" HIY "�������ԣ��������������á�����Ƭ"
                     "�̣�ȴ��$n" HIY "��������������������һ����"
                     "��˫����Ȼ����������һ�����������ھ���֮�ϣ���"
                     "�ƻֺ룬�����س���\n\n" NOR, me, this_object());

        command("nod");
        command("say ����������Ϊ���ף�����ȥ�����ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ�������졹��\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/xiang", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -3000, me);

        return 1;
}

mixed ask_skill11()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/hui", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && !query("can_learn/hong/dragon-strike", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<3000 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<120000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force", 1) < 260)
                return "������ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "��˼���ã����Ż������˵�ͷ����"
                     "�ֽ�$N" HIY "�������ԣ��������������á�����Ƭ"
                     "�̣���Ȼ$n" HIY "���μ���������һ�������ֺ���һ��"
                     "������գ����ǽ���ʮ���ơ������лڡ� ����������֮"
                     "��˵���㵽������ɽ����֮������տ�ӿ��ȥ������ʯ"
                     "���쾪�������ޱȡ�\n\n" NOR, me, this_object());

        command("nod");
        command("say ����������Ϊ���ף�����ȥ�����ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ������лڡ���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/hui", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -3000, me);

        return 1;
}

mixed ask_skill12()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/pai", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && !query("can_learn/hong/dragon-strike", me) )
                return "���������������ʶ��ô��";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<1000 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<120000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force", 1) < 260)
                return "������ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        message_sort(HIY "\n$n" HIY "��˼���ã����Ż������˵�ͷ����"
                     "�ֽ�$N" HIY "�������ԣ��������������á�����Ƭ"
                     "�̣���Ȼ$n" HIY "���μ�����ȫ�������Ķ���˫��"
                     "����ɽ����֮������տ�ӿ��ȥ������ʯ"
                     "���쾪�������ޱȡ�\n\n" NOR, me, this_object());

        command("nod");
        command("say ����������Ϊ���ף�����ȥ�����ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ���ɽ��������\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/pai", 1, me);

        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill13()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/xiao", me) )
                return "�Ҳ����Ѿ��̹�����ô��";

        if( query("family/family_name", me) != "ؤ��"
            && query("reborn/family_name", me) != "ؤ��" )
                return "���������������ʶ��ô��";

        if( !query("reborn/times", me) )
                return "�㻹δ������ת�������Ŀ��飬��������������С�";
        
        /*
        if( !query("can_perform/dragon-strike/qu", me) )
                return "�㻹δѧ��˫��ȡˮ���޷��������[���졣";
        if( !query("can_perform/dragon-strike/zhen", me) )
                return "�㻹δѧ���𾪰���޷��������[���졣";
        if( !query("can_perform/dragon-strike/hui", me) )
                return "�㻹δѧ�Ὼ���лڣ��޷��������[���졣";
        if( !query("can_perform/dragon-strike/long", me) )
                return "�㻹δѧ��������죬�޷��������[���졣";                                                
        */
        
        if (me->query_skill("dragon-strike", 1) < 1)
                return "��������ʮ���ƶ�ûѧ�������������У�";

        if( query("family/family_name", me) == "ؤ��"
            && query("family/gongji", me)<10000 )
                return "���ڰ���������Ϊ��������ʱ�����ܴ��㡣";

        if( query("shen", me)<8000000 )
                return "������֮�����ò������ҿɲ����Ĵ������㡣";

        if (me->query_skill("force", 1) < 1000)
                return "������ڹ�����㣬��ʱ���޷��������С�";

        if (me->query_skill("dragon-strike", 1) < 1000)
                return "��Ľ���ʮ���ƻ��δ��������ȥ������";

        if( query("max_neili", me)<10000 )
                return "��������Ϊ���㣬����ȥ�����ɡ�";

        message_sort(HIY "\n$n" HIY "��˼���ã����Ż������˵�ͷ����"
                     "�ֽ�$N" HIY "�������ԣ��������������á�\n\n" NOR, 
                     me, this_object());

        command("nod");
        command("say ����������Ϊ���ף�����ȥ�����ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ����[���졹��\n" NOR);
        addn("str", 1, me);
        tell_object(me, HIY "������������������һ�㡣\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dragon-strike/xiao", 1, me);
        
        if( query("family/family_name", me) == "ؤ��" )
                addn("family/gongji", -10000, me);
        me->save();

        return 1;
}
mixed ask_me()
{
        object me;
        object ob;
        object owner;

      int cost;
        me = this_player();

        if( query("family/family_name", me) != "ؤ��" )
                return "������������һ��ȥ��";

        if( query("family/master_id", me) != query("id") )
                return "�٣���ƾ��Ҳ���������ȣ�";

        if (me->query_skill("dagou-bang", 1) < 150)
                return "���������İ���Ҳ���������ȣ�";

        if( query("shen", me)<80000 )
                return "������֮�����ò����������ܽ�ؤ�����ｻ���㣿";

// ��������Ҫ��
   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "��Ϊ��ؤ��Ч��������������ӵ���㹻��ʦ�Ź��������һ�������ʹ��ʱ��ɡ�";
        ob = find_object(YUZHU);
        if (! ob) ob = load_object(YUZHU);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�����Ȳ���������������ô���������������ˣ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���������ڲ��������";

                if( query("family/family_name", owner) == "ؤ��" )
                        return "������������ʱ����ͬ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "���������������������"+query("name", owner)+
                               "���У���ȥ�����һ����ɡ�";
        }
        ob->move(me);
        ob->start_borrowing();
addn("family/gongji", -cost, me); 
        // command("give yuzhu zhang to " + me->query("id"));
        return "��������������ʱ��ȥ�ðɣ��ɱ����ؤ�ﶪ����";
}

void reset()
{
        set("book_count", 1);
}
