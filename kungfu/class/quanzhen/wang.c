// This program is a part of NT MudLIB
// wang.c

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
string ask_jiuyin();
string ask_duan();
string ask_zhipu();

void create()
{
        set_name("������", ({ "wang chongyang", "wang", "chongyang" }));
        set("long", @LONG
������ȫ��̵Ŀ�ɽ��ʦ���״��ƽ���������
���ˡ�������ƮƮ�����ۻ��䣬üĿ��񳣬��
��Щ�ɷ���ǵ�ζ����������һǻ��Ѫ����Ч
���������������ϧ��͢���ܣ����Ǳ��Ļ���
�䣬���ʱ�ִӵ��¾�������������������
�Ĵ�����Ӷ��ִ�ȫ��̡�
LONG);
        set("title", "ȫ���ɿ�ɽ��ʦ");
        set("nickname", HIW "����ͨ" NOR);
        set("age", 76);
        set("gender", "����");
        set("class", "taoist");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);
        set("max_qi", 8000);
        set("max_jing", 8000);
        set("neili", 10000);
        set("jingli", 8000);
        set("max_neili", 10000);
        set("max_jingli", 8000);
        set("jiali", 250);
        set("level", 70);
        set("combat_exp", 8000000);
        set("no_get", 1);

        set_skill("force", 650);
        set_skill("quanzhen-jianzhen", 800);
        set_skill("array", 800);
        set_skill("quanzhen-xinfa", 700);
        // set_skill("xuanmen-neigong", 380);
        set_skill("unarmed", 700);
        set_skill("xiantian-gong", 650);
        set_skill("dodge", 700);
        // set_skill("tianshan-feidu", 360);
        set_skill("jinyan-gong", 700);
        set_skill("parry", 700);
        set_skill("jinguan-yusuo", 700);
        set_skill("strike", 700);
        set_skill("chongyang-shenzhang", 660);
        set_skill("haotian-zhang", 700);
        set_skill("finger", 700);
        set_skill("zhongnan-zhi", 660);
        set_skill("sun-finger", 700);
        // set_skill("qixing-shou", 380);
        set_skill("sword", 700);
        // set_skill("qixing-jian", 360);
        // set_skill("tonggui-jian", 360);
        set_skill("quanzhen-jian", 700);
        // set_skill("tiangang-chenfa", 340);
        set_skill("taoism", 650);
        set_skill("literate", 650);
        set_skill("huajia-su", 700);
        set_skill("martial-cognize", 650);
        set_skill("medical", 680);
        set_skill("liandan-shu", 680);
        set_skill("cuff",680);
        set_skill("whip",680);
        set_skill("chunyang-quan",680);
        set_skill("duanyun-bian",680);
        set_skill("array",650);
        set_skill("beidou-zhenfa", 650);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        // map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "haotian-zhang");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "sun-finger");
        map_skill("strike", "haotian-zhang");
        // map_skill("hand", "qixing-shou");
        map_skill("cuff",   "chunyang-quan");
        map_skill("whip",   "duanyun-bian");
        prepare_skill("unarmed", "xiantian-gong");

        set("no_teach/sun-finger", "һ��ָ���Ƕμ��ش����Ҳ��ܽ��㡣");

        create_family("ȫ���", 1, "�ƽ�");

        set("inquiry", ([
                "ȫ���"     : "��ȫ��������µ����������ڡ�",
                "����"       : "����ѧʲô���У�",
                "����"       : "����ѧʲô���У�",
                "�����澭"   : (: ask_jiuyin :),
                "�λ�ү"     : (: ask_duan :),
                "������Ԫ"   : (: ask_skill1 :),
                "һ��������" : (: ask_skill2 :),
                "������"     : (: ask_skill2 :),
                "��ػ�Ԫ"   : (: ask_skill3 :),
                "��������"   : (: ask_skill4 :),
                "�����Ƶ�"   : (: ask_skill5 :),
                "������"     : (: ask_skill6 :),
                "һ��ָ"     : (: ask_zhipu :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.fen" :),
                (: perform_action, "unarmed.dang" :),
                (: perform_action, "unarmed.jian" :),
                (: perform_action, "parry.suo" :),
                (: exert_function, "hup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(__DIR__"obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 35)
        {
                command("say ������Ի������������������Ǽ���ͽ��ѧϰ�ɡ�");
                return;
        }


        if ((int)ob->query_skill("xiantian-gong", 1) < 120
           && (int)ob->query_skill("quanzhen-xinfa", 1) < 120)
        {
                command("say ��ı����ڹ��ķ�����㣬ֻ������"
                        "���Ը�������书��");
                return;
        }

        if( query("combat_exp", ob)<480000 )
        {
                command("say ���ʵս����̫������������Ը�������书��");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say �����������ұ�ѧ���˵���ּ�������Щ��"
                        "��֮�£��ҷ�������Ϊͽ��");
                return;
        }
        command("say �����������ʶ��ɴ����²����Ҿ����������ͽ���ˡ�");
        command("recruit "+query("id", ob));
}


mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hup", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "�������칦��ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "�����칦����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<2000 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ���ӻ�������ȡ����һ��"
                     "С���ӣ�ָ�����е�һ�ζ�$N" HIY "ϸ˵���ã�$N"
                     HIY "һ����һ�ߵ�ͷ��\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say ���Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������Ԫ����\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hup", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/hua", me) )
                return "��ȫ�潣���Ѵ�������裬����ûʲô�ɽ̵��ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "����ȫ�潣����ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<1600 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "������ɽ������˽⻹����͸�����о�͸���������Ұɡ�";

        if (me->query_skill("xiantian-gong", 1) < 100 &&
            me->query_skill("quanzhen-xinfa", 1) < 100)
                return "��ȫ����ڹ�����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<4800 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        message_sort(HIY "\n$n" HIY "����һЦ�����ִӵ�����˺��һ�ǲ�"
                     "�����������¼䣬ֻ���ǲ�����ʱ�����ͬ����������"
                     "�̴�������޷����������ѳ����������ʽ���������"
                     "�ȡ�ֻ����$N" HIY "Ŀ�ɿڴ���\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say ���Լ���ȥ��Ħ�ɣ��м�Ī�߽�аħ�����");
        tell_object(me, HIC "��ѧ���ˡ�һ�������塹��\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        /*
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        */
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/hua", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if( query("can_perform/quanzhen-jian/lian", me) )
                return "��ȫ�潣���Ѵ�������裬����ûʲô�ɽ̵��ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "����ȫ�潣����ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<1600 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<100000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "������ɽ������˽⻹����͸�����о�͸���������Ұɡ�";

        if (me->query_skill("quanzhen-xinfa", 1) < 100)
                return "��ȫ���ķ�����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<4800 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        command("haha");
        command("say ���Լ���ȥ��Ħ�ɣ��м�Ī�߽�аħ�����");
        tell_object(me, HIC "��ѧ���ˡ���������������\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("quanzhen-xinfa"))
                me->improve_skill("quanzhen-xinfa", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/lian", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}


mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hun", me) )
                return "�����㲻���Ѿ�ѧ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "�������칦��ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<1800 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<120000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "�����칦����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<6800 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        message_sort(HIY "\n$n" HIY "����һЦ����$N" HIY "˵���������"
                     "���칦��˾��磬ʵ������������Ϊʦ�����������к�"
                     "������˵��$n" HIY "��ڿ����ƣ���������ʾ������\n"
                     "\n" NOR, me, this_object());

        command("nod");
        command("say ��ʽ������ˣ��ܷ�����Ϳ����Լ��ˡ�");
        tell_object(me, HIC "��ѧ���ˡ���ػ�Ԫ����\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hun", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/fen", me) )
                return "�����㲻���Ѿ�ѧ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "�������칦��ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<2000 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<130000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "�����칦����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<6800 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ����$N" HIY "˵�������ѵ�"
                     "����������裬����ʦ���ʹ������У��ɿ����ˣ���$n"
                     HIY "�漴һ��������ȫ������������ת��������Χ����"
                     "�������ѡ�����΢΢һ����������������ʽ����������"
                     "��ǧ�����ˣ�����֮ǿ�������þ���ء�������������"
                     "��ֱ����$N" HIY "Ŀ�ɿڴ���\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say ��ʽ������ˣ����Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ��������𡹡�\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/fen", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/dang", me) )
                return "�����㲻���Ѿ�ѧ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "�������칦��ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<2800 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<180000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "�����칦����Ϊ���������������������ɡ�";

        if( query("max_neili", me)<8000 )
                return "���������Ϊ�Բ��㣬�������ߵ������ɡ�";

        if( !query("can_perform/xiantian-gong/fen", me) )
                return "���������ɡ��������������������㻹����ѧϰ�ɣ�";

        message_sort(HIY "\n$n" HIY "΢΢���˵�ͷ�����ִ���$N" HIY "��"
                     "���ϣ�ͻȻ$N" HIY "����ȫ�����������Ϣ������ӿ"
                     "֮�������罭�Ӿ��̣���������Ƴ�һ�㣬���ɴ󾪡�"
                     "\n\n" NOR, me, this_object());

        command("haha");
        command("say ��������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ������Ƶ�����\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/dang", 1, me);
        addn("family/gongji", -2800, me);

        return 1;
}

string ask_jiuyin()
{
        mapping fam;
        int lvl_force;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "ȫ���")
                return RANK_D->query_respect(this_player()) +
                "�뱾�̺��޹ϸ��⻰�Ӻ�˵��";
        if (!(lvl_force = this_player()->query_skill("force", 1))
            || lvl_force < 50)
                return RANK_D->query_respect(this_player()) +
                "�Ļ����ڹ�������֮ǳ��ǿ���澭�ϵ��ϳ��书�к����档";
        return "�����澭��������ѧ���ڣ����ѽ�����ʦ���ܲ�ͨ���ܡ�";
}

string ask_duan()
{
        object me=this_player();
        if( query_temp("tmark/ָ", me) == 2 )
        {
                addn_temp("tmark/ָ", 1, me);
                return("�λ�ү�ųơ��ϵۡ����Ҵ���һ��ָ��������������ָ����\n");
        }
        else {
                set_temp("tmark/ָ", 0, me);
                return("���ʶλ�ү����ô��Ī��������Ϊ�ѣ�\n");
        }
}

string ask_zhipu()
{
        object ob,me=this_player();
        if( query_temp("tmark/ָ", me) == 3 )
        {
                set_temp("tmark/ָ", 0, me);
                if(query("book_count")>0)
        {
                        ob=new(BOOK_DIR"sun_book");
                        ob->move(me);
                        addn("book_count",-1);
                        message("channel:rumor",MAG"��ҥ�ԡ�ĳ�ˣ�"+query("name", this_player())+"����һ��ָ������\n"NOR,users());
                        return("�ðɣ���������࣬��־���ᣬ�Ȿָ���׾ͽ������ˡ�\n");
                }
                else return("�������ˣ�ָ�����Ѿ�����ȡ���ˡ�\n");
        }
        else {
                set_temp("tmark/ָ", 0, me);
                return  RANK_D->query_respect(me) + "��������ҽ��������ɣ�\n";
        }
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
        case "�������" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/xiantian-gong/xian", 
                                "name"    : "�������",
                                "sk1"     : "xiantian-gong", 
                                "lv1"     : 1000, 
                                "sk2"     : "unarmed", 
                                "lv2"     : 1000, 
                                "sk3"     : "force",
                                "lv3"     : 1000, 
                                "reborn"  : 1,
                                "gongxian": 3000, ])); 
                break; 
       case "�����޹�" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                            ([ "perform" : "can_perform/duanyun-bian/guang", 
                       "name"    : "�����޹�",
                 "sk1"     : "duanyun-bian", 
                  "lv1"     : 120, 
                 "neili"   : 1400, 
                    "shen"    : 24000, ])); 
                break; 
        case "��������" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/duan", 
                        "name"    : "��������",
                  "sk1"     : "duanyun-bian", 
                   "lv1"     : 220, 
                  "neili"   : 2400, 
                  "gongxian"   : 1400, 
                              "shen"    : 44000, ])); 
                 break; 
        case "���Ʊ�ɫ" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/bian", 
                        "name"    : "���Ʊ�ɫ",
        "sk1"     : "duanyun-bian", 
         "lv1"     : 320, 
        "neili"   : 4400, 
            "gongxian"   : 2400, 
                                "shen"    : 44000, ])); 
                 break; 
                return 0; 
        } 
} 

/*
void unconcious()
{
        die();
}
*/
