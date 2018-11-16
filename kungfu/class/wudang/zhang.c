// This program is a part of NITAN MudLIB
// zhang.c ������

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
// inherit F_NOCLONE;
inherit F_QUESTER;

#include <ansi.h>
#include "wudang.h"

#define CANPIAN         "/kungfu/class/wudang/obj/canpian"
// #define ZHENWU_SWORD    "/clone/unique/zhenwu_jian"
#define ZHENWU_SWORD    "/clone/lonely/zhenwu"

mixed ask_jian();
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
mixed ask_medicine();
mixed ask_to_learn_jy();
int try_to_learn_jy();


void create()
{
        object ob;
        set_name("������", ({ "zhang sanfeng", "zhang" }));
        set("nickname", "��������");
        set("long",
                "������䵱�ɿ�ɽ���桢�������ֵ�̩ɽ�������������ˡ�\n"
                "��������һϮ�ۻ�ĻҲ����ۣ����θߴ��쳣���뷢������\n"
                "���Ϻ���⻬��Ц���е����ǿ��ף�����Ҳ��������״��\n");
        set("gender", "����");
        set("age", 100);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 14123);
        set("max_jing", 3173);
        set("wudang_book", 1);
        set("eff_jingli", 9000);
        set("max_jingli", 9000);
        set("neili", 12000);
        set("max_neili", 12000);
        set("jiali", 300);
        set("combat_exp", 6500000);
        set("score", 650000);

        set_skill("array", 600);
        set_skill("zhenwu-jianzhen", 600);
        set_skill("force", 600);
        set_skill("taiji-shengong", 600);
        set_skill("wudang-jiuyang", 600);
        set_skill("yinyun-ziqi", 600);
        set_skill("dodge", 600);
        set_skill("tiyunzong", 600);
        set_skill("cuff", 600);
        set_skill("taiji-quan", 600);
        set_skill("strike", 600);
        set_skill("wudang-zhang", 600);
        set_skill("hand", 600);
        set_skill("paiyun-shou", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("wudang-jian", 600);
        set_skill("blade", 600);
        set_skill("taiji-dao", 600);
        set_skill("taiji-jian", 600);
        set_skill("taoism", 600);
        set_skill("literate", 600);
        set_skill("wudang-yaoli", 600);
        set_skill("medical", 600);
        set_skill("liandan-shu", 600);
        set_skill("martial-cognize", 600);
        set_skill("tianwei-zhengqi", 600);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("strike", "wudang-zhang");
        map_skill("blade", "taiji-dao");

        prepare_skill("cuff", "taiji-quan");

        create_family("�䵱��", 1, "��ɽ��ʦ");
        set("class", "taoist");

        set("inquiry", ([
                "���佣"     : (: ask_jian : ),
                "���쾢"     : (: ask_skill1 :),
                "���־�"     : (: ask_skill2 :),
                "���־�"     : (: ask_skill3 :),
                "���־�"     : (: ask_skill4 :),
                "ճ�־�"     : (: ask_skill5 :),
                "̫��ͼ"     : (: ask_skill6 :),
                "���־�"     : (: ask_skill7 :),
                "���־�"     : (: ask_skill8 :),
                "���־�"     : (: ask_skill9 :),
                "�����ת"   : (: ask_skill10 :),
                "�����а"   : (: ask_skill11 :),
                "̫������"   : (: ask_skill12 :),
                "������"     : (: ask_medicine :),
                "��ҩ"       : (: ask_medicine :),
                "�䵱����"   : (: ask_to_learn_jy :),
                "���Ʊ�����" : "����ѧ�������������Ժ��Լ��ưɡ�",
                "����ɢ"     : "��...����ͨ�����������İ���Լ������ưɡ�",
                "��ָ�ὣ"   : "������ȥ������Īʦ�ְ�......",
        ]));

        set("no_teach", ([
                   "wudang-jiuyang" : (: try_to_learn_jy() :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.jia" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "sword.zhuan" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "cuff.tu" :),
                (: perform_action, "cuff.zhen" :),
                (: perform_action, "cuff.zhan" :),
                (: perform_action, "cuff.ji" :),
                (: perform_action, "cuff.yin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set("master_ob", 5);
        setup();
        if (clonep())
        {
                ob = find_object(ZHENWU_SWORD);
                if (! ob) ob = load_object(ZHENWU_SWORD);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object("/d/wudang/obj/greyrobe")->wear();

        set("startroom", "/d/wudang/xiaoyuan");
        // check_clone();
}

void scan()
{
        ::scan();

        if (! query_temp("weapon"))
                map_skill("parry", "taiji-quan");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 120)
        {
                command("say ���䵱�����ڼ��书���������ڹ��ķ���");
                command("say " + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�����������϶��µ㹦��");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }

        if (ob->query_skill("taoism", 1) < 120)
        {
                command("say ���䵱���书ȫ�ӵ��������");
                command("say ��Ե����ķ������򻹲�����");
                command("say " + RANK_D->query_respect(ob) + "���Ƕ��о��о���ѧ�ķ��ɡ�");
                return;
        }

        if (ob->query_int() < 32)
        {
                command("say ���䵱���书���迿�Լ�����");
                command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
                command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
                return;
        }

        command("smile");
        command("say �벻���ϵ��ڴ���֮�꣬���ٵ�һ������֮�ţ����ǿ�ϲ�ɺء�");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-shengong/dian", me) )
                return "�Ҳ����Ѿ��̸�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-shengong", 1) < 1)
                return "����̫���񹦶�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<150000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-shengong", 1) < 100)
                return "���̫������Ϊ̫ǳ���������������ɡ�";

        if( query("max_neili", me)<1500 )
                return "���������Ϊ̫ǳ���������������ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ�����һָ��������磬��Ȼ"
                     "����$N" HIY "��Ե���ִ���$N" HIY "��ʱֻ��$n" HIY
                     "������ԴԴ����������ӿ�룬ȫ��һ�����飬������"
                     "ʧɫ��\n\n" NOR, me, this_object());

        command("say �㶮����");
        tell_object(me, HIC "��ѧ���ˡ����쾢����Ծ�ϡ���\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("taiji-shengong"))
                me->improve_skill("taiji-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-shengong/dian", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhen", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "����̫��ȭ��ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<300 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<100000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "���̫��ȭ��Ϊ̫ǳ���������������ɡ�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ̫ǳ���������������ɡ�";

        message_sort(HIY "\n$n" HIY"�����𻰣�����վ������������������"
                     "������ǰ����۰뻷������Գ����ƣ����Ʒ���������"
                     "������ȸβ�����ޡ��������ơ�����Ʊա�ʮ���֡���"
                     "����ɽ����һ��һʽ������ȥ����$n" HIY "ʹ���ϲ���"
                     "̽���ϲ���ȸβ�����޶���̫���������е�վ�ڵ�"
                     "�ء����$n" HIY "˫�ֺϱ�̫��Ȧ�������$N" HIY
                     "�ʵ���������ȭ���С����鶥�������ذα�����������"
                     "������׹�⡹�ľ��ϣ����������˶��٣���\n\n" NOR,
                     me, this_object());

        command("say �������У���������������һ������·ȭ����Ҫּ��");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/zhen", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/yin", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "����̫��ȭ��ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<200 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<100000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "���̫��ȭ��Ϊ̫ǳ���������������ɡ�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ̫ǳ���������������ɡ�";

        message_sort(HIY "\n$n" HIY"�����𻰣�����վ������������������"
                     "������ǰ����۰뻷������Գ����ƣ����Ʒ���������"
                     "������ȸβ�����ޡ��������ơ�����Ʊա�ʮ���֡���"
                     "����ɽ����һ��һʽ������ȥ����$n" HIY "ʹ���ϲ���"
                     "̽���ϲ���ȸβ�����޶���̫���������е�վ�ڵ�"
                     "�ء����$n" HIY "˫�ֺϱ�̫��Ȧ�������$N" HIY
                     "�ʵ���������ȭ���С����鶥�������ذα�����������"
                     "������׹�⡹�ľ��ϣ����������˶��٣���\n\n" NOR,
                     me, this_object());

        command("say ���ⲻ������̫��Բת����ʹ�ԶϾ���");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/ji", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "����̫��ȭ��ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<400 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<120000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "���̫��ȭ��Ϊ̫ǳ���������������ɡ�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ̫ǳ���������������ɡ�";

        message_sort(HIY "\n$n" HIY"�����𻰣�����վ������������������"
                     "������ǰ����۰뻷������Գ����ƣ����Ʒ���������"
                     "������ȸβ�����ޡ��������ơ�����Ʊա�ʮ���֡���"
                     "����ɽ����һ��һʽ������ȥ����$n" HIY "ʹ���ϲ���"
                     "̽���ϲ���ȸβ�����޶���̫���������е�վ�ڵ�"
                     "�ء����$n" HIY "˫�ֺϱ�̫��Ȧ�������$N" HIY
                     "�ʵ���������ȭ���С����鶥�������ذα�����������"
                     "������׹�⡹�ľ��ϣ����������˶��٣���\n\n" NOR,
                     me, this_object());

        command("say ���μǽ���������������������ʩ����");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/ji", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhan", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "����̫��ȭ��ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<500 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<140000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "���̫��ȭ��Ϊ̫ǳ���������������ɡ�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ̫ǳ���������������ɡ�";

        message_sort(HIY "\n$n" HIY"�����𻰣�����վ������������������"
                     "������ǰ����۰뻷������Գ����ƣ����Ʒ���������"
                     "������ȸβ�����ޡ��������ơ�����Ʊա�ʮ���֡���"
                     "����ɽ����һ��һʽ������ȥ����$n" HIY "ʹ���ϲ���"
                     "̽���ϲ���ȸβ�����޶���̫���������е�վ�ڵ�"
                     "�ء����$n" HIY "˫�ֺϱ�̫��Ȧ�������$N" HIY
                     "�ʵ���������ȭ���С����鶥�������ذα�����������"
                     "������׹�⡹�ľ��ϣ����������˶��٣���\n\n" NOR,
                     me, this_object());

        command("say ��ֻ�趮��̫��ͼԲת���ϡ������仯֮�⼴�ɡ�");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�ճ�־�����\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        set("can_perform/taiji-quan/zhan", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/tu", me) >= 10 )
                return "��ѧ���㶼�Ѿ�ѧ�ˣ��Ժ�Ҫ�Ƽ����ã�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "����̫��ȭ��ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<3000 )
                return "��Ϊ���䵱��Ч���������������Ҳ�æ���㡣";

        if( query("shen", me)<250000 )
                return "������������������û������࣬�Ҳ��ܷ��Ĵ�����У�";

        if (me->query_skill("taiji-quan", 1) < 250)
                return "���̫��ȭ���������ң�Ҫ��������";

        if (me->query_skill("taiji-shengong", 1) < 300)
                return "���̫���񹦻������ң��ú����аɣ�";

        if (me->query_skill("taoism", 1) < 300)
                return "��ĵ�ѧ�ķ��о��Ļ��������ף�Ҫ�¹����ѧ���ǣ�";

        if( query("max_jingli", me)<1000 )
                return "��ľ������ã����㴫����̫��ͼ��Ҳ�������á�";

        message_sort(HIY "\n$n" HIY "���ͷ��˫�����Ữ��һ��Ȧ�ӣ�����"
                     "�����޶������ֽ������¡�\n" NOR, me,
                     this_object());

        command("say �㿴���˶��٣�");

        if( query("potential", me)<query("learned_points", me)+100 )
        {
                tell_object(me, "�㿴�˰��죬û���о���ʲô��"
                      "�Ķ�����������Ǳ�ܻ�������\n");
                return 1;
        }

        addn("learned_points", 100, me);

        if( addn("can_perform/taiji-quan/tu", 1, me)<10 )
        {
                message_vision(HIY "$N" HIY "����ãã�ĵ���"
                               "��ͷ����˼���á�\n\n" NOR, me);
                tell_object(me, HIC "���̫��ͼ����һ������\n" NOR);
        } else
        {
                message_sort(HIY "$N" HIY "��¶Ц�ݣ�ϲ�������Ѿ�������"
                             "����ν���������ʵ���޷ֱ𰡣�$n" HIY "��"
                             "����Ц�������׾ͺã����׾ͺã��Ժ��������"
                             "ʹ�ã���ȥ�ɡ�\n\n", me, this_object());

                tell_object(me, HIC "��ѧ���˵����ܼ���̫��ͼ����\n" NOR);
                if (me->can_improve_skill("taoism"))
                        me->improve_skill("taoism", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("taiji-shengong"))
                        me->improve_skill("taiji-shengong", 1500000);
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 1500000);
                if (me->can_improve_skill("taiji-quan"))
                        me->improve_skill("taiji-quan", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                addn("family/gongji", -3000, me);
                set("can_perform/taiji-quan/tu", 10, me);
        }
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/chan", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<300 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<80000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 80)
                return "���̫�������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "΢΢Ц��Ц�����һָ����ָ��������"
                     "ʼ��������ʾ���С���������һֱ����ʮ��ʽ��ָ���롹"
                     "��˫��ͬʱ��Բ�����ɵ���ʮ��ʽ���ֽ���ԭ����ֱ��һ"
                     "�׽�����ʾ��ϣ�$n" HIY "�����$N" HIY "�ʵ�������"
                     "̫�������еĽ��⣬���������˶��٣���\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say ��ֻ���ס�����޶������಻����ɡ�");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/chan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/sui", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<200 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<80000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 60)
                return "���̫�������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "΢΢Ц��Ц�����һָ����ָ��������"
                     "ʼ��������ʾ���С���������һֱ����ʮ��ʽ��ָ���롹"
                     "��˫��ͬʱ��Բ�����ɵ���ʮ��ʽ���ֽ���ԭ����ֱ��һ"
                     "�׽�����ʾ��ϣ�$n" HIY "�����$N" HIY "�ʵ�������"
                     "̫�������еĽ��⣬���������˶��٣���\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say �������Ķ��������Ķ��գ�����Բת���⡣");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/sui", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jia", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<600 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<100000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 150)
                return "���̫�������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "΢΢Ц��Ц�����һָ����ָ��������"
                     "ʼ��������ʾ���С���������һֱ����ʮ��ʽ��ָ���롹"
                     "��˫��ͬʱ��Բ�����ɵ���ʮ��ʽ���ֽ���ԭ����ֱ��һ"
                     "�׽�����ʾ��ϣ�$n" HIY "�����$N" HIY "�ʵ�������"
                     "̫�������еĽ��⣬���������˶��٣���\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say ����������������ǧ���֮Ϊ̫����");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����־�����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/jia", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhuan", me) )
                return "���Լ��������ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<120000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 160)
                return "���̫�������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "΢΢Ц��Ц�����һָ����ָ��������"
                     "ʼ��������ʾ���С���������һֱ����ʮ��ʽ��ָ���롹"
                     "��˫��ͬʱ��Բ�����ɵ���ʮ��ʽ���ֽ���ԭ����"
                     "̫�������еĽ��⣬���������˶��٣���\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say ���޾�������Ԧ����");
        command("say ���������ˣ���ȥ���������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������ת����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhuan", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill11()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhenwu", me) )
        return "�Լ��úö���ϰ�ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<2000 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<120000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 180)
                return "���̫�������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "΢΢��ף����ּ���һ����֦��$N" HIY
                     HIY "ɨ����$N" HIY "������ƽ�����棬������Ϊ�ɻ�"
                     "ֻ������һ������Ȼֻ��$n" HIY "���ƴ�䣬���ȷǷ�"
                     "���仯���$N" HIY "���һ�������Ҳ�����\n\n" NOR,
                     me, this_object());

        command("say ��������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ������а����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhenwu", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill12()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jian", me) )
                return "�Լ��úö���ϰ�ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if( !query("reborn/times", me) )
                return notify_fail("�㻹û�о���ת�������Ŀ��飬�޷�����������С�\n");
                
        if (me->query_skill("taiji-jian", 1) < 1)
                return "����̫��������ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<5000 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣����Ҫ5000�����ɹ��ף�";

        if( query("shen", me)<500000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�����Ҫ����50��";

        if (me->query_skill("taiji-jian", 1) < 1000)
                return "���̫�������������ң�Ҫ��������";

        if (me->query_skill("tianwei-zhengqi", 1) < 200)
                return "������ɼ�������������û���������ң�Ҫ��������";
        
        message_sort(HIY "\n$n" HIY "����һת������֮���������������̲�����������"
                              "��������̬Ʈ������֮�����ľ�$HIG$̫�O$HIY$֮�⡭��\n\n$N" 
                              HIY "���ŵ������еĹؼ�����Ҫ����̫�����⣬�Ӷ���̫����"
                              "�������ӵ�������\n\n" NOR, me, this_object());

        command("haha");
        command("say ��������ˣ�");        
        tell_object(me, HIC "��ѧ���ˡ�̫�O���⡹��\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        if (me->can_improve_skill("martial-cognize"))             
                me->improve_skill("martial-cognize", 1500000);
                
        set("can_perform/taiji-jian/jian", 1, me);
        addn("family/gongji", -5000, me);

        return 1;
}

mixed ask_jian()
{
        int cost;
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "�䵱��" )
                        message_vision(CYN "$N" CYN "��ŭ����$n" CYN "����������Ϊ�䵱���ӣ�"
                                       "��������ħ�������������ת����\n" NOR,
                                       this_object(), me);
                else
                message_vision(CYN "$N" CYN "��ŭ����$n" CYN "�ȵ�������һ��аħ��"
                               "������Ȼ�ҿ������佣����\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "�䵱��" )
                return "���佣�������䵱����֮�������������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ��������佣���㻹����ذɡ�";

        if( query("shen", me)<60000 )
                return "������������������ò������Ҳ��ܰ����佣�����㡣";

        if( query("family/first", me) ) cost = 250;
        else cost = 500;
        if( query("family/gongji", me) < cost )
                return "��Ϊ���䵱��Ч��������������ӵ���㹻��ʦ�Ź��������һ����佣ʹ��ʱ��ɡ�";

        ob = find_object(ZHENWU_SWORD);
        if (! ob) ob = load_object(ZHENWU_SWORD);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "���佣�������������ô����ô�����������أ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���Ѿ������佣�Ѿ����ȥ�ˡ�";

                if( query("family/master_id", owner) == query("id") )
                        return "���佣������"+query("name", owner)+
                               "���У���Ҫ���þ�ȥ�����ɡ�";
                else
                        return "���佣��������"+query("name", owner)+
                               "���У���ȥ�����һ����ɡ�";
        }

        ob->move(this_object());
        ob->start_borrowing();
        message_vision(CYN "$N" CYN "���ͷ�������ã����������佣Ҫ����һЩ��"
                       "����������飡��\n" NOR, this_object(), me);
        command("give zhenwu jian to "+query("id", me)); 
        addn("family/gongji", -cost, me);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHENWU_SWORD)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��л��λ" + RANK_D->query_respect(me) + "�����佣���ء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}

mixed ask_medicine()
{
        object me;
        object ob;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
        {
                command("say ����ʲô�ˣ������ҵ�ҽ���к�Ŀ�ģ�");
                return 1;
        }

        if ((int)me->query_skill("liandan-shu", 1) < 100)
        {
                command("say ������������˽�̫ǳ������ѧ����"
                        "��һЩ�Ҳ��ܰ��ر������㡣");
                return 1;
        }

        if (query("wudang_book") < 1)
        {
                command("say ���ǿ�ϧ���������ˣ������Ѿ����ȥ�ˡ�");
                return 1;
        }

        addn("wudang_book", -1);
        ob = new("/clone/book/wudang");
        message_vision("$n����һ�����Ƶı����ӵݸ�$N������"
                       "�������������Ȿ���úÿ�����\n",
                       me, this_object());
        ob->move(me, 1);
        return 1;
}

/*
mixed ask_to_learn_jy()
{
        object *obs, obj, player = this_player();

        if( query("family/master_id", player) != "zhangsanfeng" )
        {
                return "̫���������䵱������֮����\n";
        }
        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
                return "��ʦ��Զ��ʦ���ھ��ģ�����ѧ��ȫ��������չ����Σ�"+
                       "������У���ֻ����ͨ�����ĳɡ�\n";
        case 5:
        case 6:
        case 7:
        case 8:
                return "��ʦ��Զ��ʦѧ�á������澭����Բ��֮ǰ���о��ģ�����Ů����"+
                       "��������ɫ��ʦ�������˸��Լǵ�һ���֣�\n" +
                       "����䵱�����ҡ����������书�������ʮ������ͥ�����������֡�\n";
        case 9:
                if (player->query_skill("taiji-shengong", 1) < 200)
                {
                        return "��Ĺ�����ǳ���ú�ѧȫ���䵱̫������˵�ɡ�\n";
                }

                obj = 0;
                obs = filter_array(children(CANPIAN), (: clonep :));
                if (sizeof(obs) > 0) obj = obs[0];

                if (objectp(obj) && objectp(environment(obj)) &&
                    userp(environment(obj)))
                {
                        return "�����񹦲�ƪ����ʦ�ֵܽ����ˣ���ȥ�����ǰ�\n";
                }
                if (! objectp(obj)) obj = new(CANPIAN);
                obj->move(player);
                message_vision("$N��$nһ�������񹦲�ƪ��\n", this_object(), player);
                command("rumor"+query("name", this_player())+"Ū����һ��"NOR+YEL"�����񹦲�ƪ"HIM"��"NOR);
                return "�ҽ����мǵõ�һЩ�����񹦱�¼�ڴˣ�\n"+
                       "�����һλ�����ɸ�����֮��ͬ����(canwu)��Ҳ�����⹦������ʧ����\n";
        }
        return 0;
}
*/

mixed ask_to_learn_jy()
{
        object ob;
        object me;
        me = this_player();

        if( query("can_learn/jiuyang-shengong/wudang", me) )
                return "�ϵ��Ѿ���Ӧ�������䵱�������ˣ�����ô����ô���£�";

        if( !query("can_learn/jiuyang-shengong/kunlun", me) )
                return "���ա������澭������ʦ����Զ��ʦ���ж�ʧ������Ҳ��֪������η���";

        if( !query("can_learn/jiuyang-shengong/shaolin", me) )
                return "���������ʱ�ܹ�׷�ء������澭������Զ��ʦҲ���������ѡ�";

        message_vision(CYN "\n��������ϸ������$N" CYN "��һ��Ŀ�ⶸȻһ����\n\n" NOR, me);

        command("say �㲻���ǵ��껹�;������Զ��ʦ֮����");
        command("say ��ν���������л������������ϵ�����ͨ��һ�㣬���ѻ�Ϊ�䵱��������");
        command("say ������²��������ϵ����ǿ��Խ����׾������������㡣");

        tell_object(me, HIC "������ͬ�⴫���㡸�䵱����������\n" NOR);

        if (me->can_improve_skill("martial-cognize"))
                improve_skill("martial-cognize", 1500000);

        set("can_learn/jiuyang-shengong/wudang", 1, me);
        return 1;
}

int try_to_learn_jy()
{
        object me = this_player();

        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say �䵱���������Ǿ����񹦵ķ�֧������"
                                "��ʱ��ʦ����Զ��ʦ���ڡ�");
                        command("say ��������ƶ���ز���ʶ����̸���ϡ�ָ��"
                                "�����֣�");
                        return -1;
                } else
                {
                        command("say �䵱���������Ǿ����񹦵ķ�֧������"
                                "��ʱ��ʦ����Զ��ʦ���ڡ�");
                        command("say ��Ȼ���书�������������Ķ�����������"
                                "���ֵ��书���������ҵĵ���Ҳ�����ڡ�");
                        return -1;
                }
        }

        if (me->query_skill("wudang-jiuyang") > 400)
        {
                command("say ����䵱������������Ϊ����ˣ��Ժ�����Լ��о��ɡ�");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("say �ϵ��������Ĵ������������������аħ������֮�");
                command("say ����Ĺ����º��������ϵ��Ұɡ�");
                return -1;
        }
        return 0;
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say �䵱���������Ǿ����񹦵ķ�֧������"
                                "��ʱ��ʦ����Զ��ʦ���ڡ�");
                        command("say ��������ƶ���ز���ʶ����̸���ϡ�ָ��"
                                "�����֣�");
                        return -1;
                } else
                {
                        command("say �䵱���������Ǿ����񹦵ķ�֧������"
                                "��ʱ��ʦ����Զ��ʦ���ڡ�");
                        command("say ��Ȼ���书�������������Ķ�����������"
                                "���ֵ��书���������ҵĵ���Ҳ�����ڡ�");
                        return -1;
                }
        }

        if (skill != "wudang-jiuyang")
        {
                command("say ��ѧ�Ӷ�����Ҳ�����ã��㻹��ר��ѧϰ�䵱�������ɡ�");
                return -1;
        }
        return 1;
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

        case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tiyunzong/zong",
                           "name"    : "���־�",
                           "sk1"     : "tiyunzong",
                           "lv1"     : 150,
                           "sk2"     : "dodge",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 24000, ]));
                break;

        case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/lian",
                           "name"    : "���־�",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 120,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 120,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;
        case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-quan/an",
                           "name"    : "���־�",
                           "sk1"     : "taiji-quan",
                           "lv1"     : 200,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 200,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

/*
        case "̫������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/jian",
                           "name"    : "̫������",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 1000,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 1000,
                           "gongxian": 3000,
                           "neili"   : 2000,
                           "reborn"  : 1,
                           "shen"    : 28000, ]));
                break;
*/

        default:
                return 0;
        }
}
