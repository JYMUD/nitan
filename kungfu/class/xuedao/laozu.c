// This program is a part of NT MudLIB

#include <ansi.h>
#include "xuedao.h"

//#define XUEDAO    "/clone/unique/xuedao"
#define XUEDAO    "/clone/lonely/xhsblade"
#define JING      "/clone/book/xuedao-book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();

mixed ask_dao();
mixed ask_book();
mixed ask_midao();

void create()
{
        object ob;
        set_name("Ѫ������", ({ "xuedao laozu", "xuedao", "laozu", "xue", "lao" }));
        set("long", @LONG
���������Ż��ۣ���ͼ��ϣ���ͷ���������϶���
���ơ�������Ѫ���ŵ��Ĵ����š�
LONG);
        set("gender", "����");
        set("age", 85);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 33);
        set("int", 31);
        set("con", 35);
        set("dex", 32);
        set("max_qi", 5500);
        set("max_jing", 4000);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 3500000);

        set_skill("force", 600);
        set_skill("mizong-neigong", 600);
        set_skill("xuehai-mogong", 600);
        set_skill("blade", 600);
        set_skill("xuedao-daofa", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
/*
        set_skill("force", 480);
        set_skill("mizong-neigong", 480);
        set_skill("xuehai-mogong", 480);
        set_skill("blade", 480);
        set_skill("xuedao-daofa", 460);
        set_skill("sword", 440);
        set_skill("mingwang-jian", 440);
        set_skill("dodge", 460);
        set_skill("shenkong-xing", 460);
        set_skill("hand", 460);
        set_skill("dashou-yin", 460);
        set_skill("cuff", 460);
        set_skill("yujiamu-quan", 460);
        set_skill("parry", 460);
        set_skill("lamaism", 440);
        set_skill("literate", 460);
        set_skill("martial-cognize", 300);
*/

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ying" :),
                (: perform_action, "blade.chi" :),
                (: perform_action, "blade.xue" :),
                (: perform_action, "blade.shi" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
                (: exert_function, "resurrect" :),
                (: exert_function, "powerup" :),

        }) );

        create_family("Ѫ����", 4, "����");
        set("class", "bonze");

        set("inquiry", ([
                "Ѫ��"      : (: ask_dao :),
                "Ѫ����"    : (: ask_book :),
                "�ܵ�"      : (: ask_midao :),
                "�ص�"      : (: ask_midao :),
                // "ԡѪ����"  : (: ask_skill1 :),
                "���ӡ"    : (: ask_skill2 :),
                "���޽���"  : (: ask_skill3 :),
                "����"      : (: ask_skill4 :),
                "��ħ"      : (: ask_skill5 :),
                "��Ӱ��"  : (: ask_skill6 :),
                "������"  : (: ask_skill7 :),
                "��Ѫ��"  : (: ask_skill8 :),
                "��Ѫ��"  : (: ask_skill9 :),
                // "���ӿ���"  : "��һ����ȥ��ʤ�н�����ˡ�",
                // "���ǻ���"  : "��һ����ȥ�ñ��������ˡ�",
                "Ѫ���ޱ�"  : "�٣���������ȥ�������ӿڣ��������Ҹ��",
        ]));

        set("master_ob", 5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                ob = find_object(XUEDAO);
                if (! ob) ob = load_object(XUEDAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("clone/weapon/jiedao");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        add_money("silver", 20);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "Ů��" )
        {
                command("say �Ϸ���Ůͽ�ܣ����������������档\n");
                return;
        }

        if( query("gender", ob) != "����" )
        {
                command("say ��ƽ������ߵľ������ˣ��ٲ�������ɱ���㣡\n");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                set_temp("pending/join_bonze", 1, ob);
                command("say �㲻�ǳ����ˣ�����Ѫ�����ǲ��������ġ�"
                        "�����Ҫ���ң�ȥ�����¡�");
                return;
        }

        if( query("combat_exp", ob)<350000 )
        {
                command("say ���ʵս����Ҳ߯���ˣ���ȥ�úø�������ȥ��");
                return;
        }

        if( query("shen", ob)>-50000 )
        {
                command("say ���ǲ����������������ɱ�˶����ᣡ\n");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 140)
        {
                command("say ��˵զ��ƽʱ��ɱ���ӣ����ܹ�Ҳ���Ƿ��ŵ��ӡ�\n");
                command("say ��������ڷ���ߺ��������Ұɡ�\n");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 100 &&
            (int)ob->query_skill("xuehai-mogong", 1) < 100)
        {
                command("say ����������ô���ģ��ڹ���ô�\n");
                return;
        }

        if ((int)ob->query_skill("blade", 1) < 120)
        {
                command("say �㵶����ô������������ң�\n");
                return;
        }

        command("sneer");
        command("say �����Ժ�͸����Ϸ���ˡ�");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/resurrect", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "����Ѫ���󷨶�ûѧ��������ʲô��";

        if( query("family/gongji", me)<500 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-60000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if( query("max_neili", me)<1000 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("xuedao-daofa", 1) < 120)
                return "�����Ѫ�����������������Ϸ�";

        message_vision(HIY "$n" HIY "΢΢һЦ������Ҳ���𻰣�ֻ��������֣������"
                       "��\n$N" HIY "�ؿڡ�����$N" HIY "�ɻ�䣬ȴ��$n" HIY "�ƾ�"
                       "���£�$N" HIY "��ʱȫ��\nһ�������������������޲��泩"
                       "��˵���������á�\n" NOR, me, this_object());

        command("sneer");
        command("say ������ô��");
        tell_object(me, HIC "��ѧ���ˡ�ԡѪ��������\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/resurrect", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/dashou-yin/yin", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("dashou-yin", 1) < 1)
                return "��������ӡ��ûѧ��������ʲô��";

        if( query("family/gongji", me)<200 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-15000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 140)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<1000 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("dashou-yin", 1) < 100)
                return "����Ѵ���ӡ�������������Ϸ�";

        message_vision(HIY "$n" HIY "��Цһ�������´�����$N" HIY "һ�������˵�ͷ"
                       "����������\n���ģ�����ׯ�أ�˫��Я�ž��������$N" HIY "��ǰ"
                       "��һ����������\n���䣬��ʱֻ����Ȼһ�����죬�����ڵ����"
                       "��$n" HIY "����\n���������Ĵ������������������������ɢ"
                       "��$N" HIY "��ŷ���\n�������������ϻ�ȻǶ��һ˫��ӡ��\n"
                       NOR, me, this_object());

        command("nod");
        command("say ֻҪ�ڹ����������в���������");
        tell_object(me, HIC "��ѧ���ˡ����ӡ����\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("dashou-yin"))
                me->improve_skill("dashou-yin", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dashou-yin/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/yujiamu-quan/jiang", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("yujiamu-quan", 1) < 1)
                return "����������ĸȭ��ûѧ��������ʲô��";

        if( query("family/gongji", me)<300 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-18000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 150)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<1200 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("yujiamu-quan", 1) < 100)
                return "����ѽ�����ĸȭ�������������Ϸ�";

        message_vision(HIY "$n" HIY "��΢���˵�ͷ���������һ�������ݲ���ǰ����Ŀ"
                       "��\n�ȣ�ȭ�е��������籼�ף���ʱ����$N" HIY "������ȭ����"
                       "ʽ��Ϊ��\n�ʵ��$N" HIY "ǰ��δ�š�\n" NOR, me,
                       this_object());;

        command("haha");
        command("say ������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ����޽�������\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("yujiamu-quan"))
                me->improve_skill("yujiamu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yujiamu-quan/jiang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/ruo", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "����������������ûѧ��������ʲô��";

        if( query("family/gongji", me)<100 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-10000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 140)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<1200 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("mingwang-jian", 1) < 100)
                return "����Ѳ����������������������Ϸ�";

        message_vision(HIY "$n" HIY "��Цһ����Ҳ���𻰣���$N" HIY "���нӹ�����"
                       "����������\nһ����������ʱ����һ��ͳ������������������"
                       "$N" HIY "ֻ�е���\nͷһ�𣬾�ӿ��һ��Ī���ı�����\n" NOR,
                       me, this_object());

        command("haha");
        command("say ����ܼ򵥣����Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/ruo", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/xiang", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "����������������ûѧ��������ʲô��";

        if( query("family/gongji", me)<400 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-15000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 180)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<1600 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("mingwang-jian", 1) < 140)
                return "����Ѳ����������������������Ϸ�";

        message_vision(HIY "$n" HIY "��$N" HIY "΢΢һЦ���漴������֣���ʳ��ָ"
                       "��£������\n���������͡���һ���յ��������ʱ�ƿ�֮������"
                       "��һ������\n��ָ��ŷ�����$N" HIY "��������ɮ�۴�͸��һ��"
                       "С�ס�\n" NOR, me, this_object());

        command("sneer");
        command("say ���в�������Խ���ý���������ˡ�");
        tell_object(me, HIC "��ѧ���ˡ���ħ����\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/xiang", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/ying", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "����Ѫ���󷨶�ûѧ��������ʲô��";

        if( query("family/gongji", me)<300 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-60000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 160)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<1500 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("xuedao-daofa", 1) < 120)
                return "�����Ѫ�����������������Ϸ�";

        message_vision(HIY "$n" HIY "��Цһ������$N" HIY "˵��������ͽ�����Ϸ���"
                       "�͸�����ʾ\nһ�飬�����ˣ���$n" HIY "˵���������Ѫ����"
                       "��Ȼһ����\n�ȣ������е�Ѫ���趯���֣���ʱ���漤����Ѫ"
                       "�˱���$N" HIY "��\nȥ��ֱ������$N" HIY "Ŀ�ɿڴ���\n" NOR,
                       me, this_object());

        command("haha");
        command("say ���е�Ҫ������һ�����֣�������ô��");
        tell_object(me, HIC "��ѧ���ˡ���Ӱ�񵶡���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/ying", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/chi", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "����Ѫ���󷨶�ûѧ��������ʲô��";

        if( query("family/gongji", me)<800 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-70000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 220)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<2400 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("xuedao-daofa", 1) < 160)
                return "�����Ѫ�����������������Ϸ�";

        message_vision(HIY "$n" HIY "�ٺ�һЦ�����ֽ�$N" HIY "�е���ǰ��������$N"
                       HIY "�����ֹ���\n���졣���$n" HIY "�ְγ������Ѫ��������"
                       "�£��ƺ���һ��\n��Ϊ����ĵ�����\n" NOR, me, this_object());

        command("haha");
        command("say ��Ҫ�Ҷ��������ˣ��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������񵶡���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/chi", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/xue", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "����Ѫ���󷨶�ûѧ��������ʲô��";

        if( query("family/gongji", me)<1000 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-80000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 220)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<2400 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("xuedao-daofa", 1) < 160)
                return "�����Ѫ�����������������Ϸ�";

        message_vision(HIY "$n" HIY "���˿�$N" HIY "����Цһ�������˵�ͷ�������ֽ�"
                       "$N" HIY "�е���\nǰ��������$N" HIY "�����ֹ��˰��졣$N" HIY
                       "������ɫ��䣬�ƺ�������\nʲô�������ŵ����飬��$n" HIY "��"
                       "��������һ��$N" HIY "�ı���\n�������ɳ����������漴���ĵ�"
                       "һЦ��������������\n" NOR, me, this_object());

        command("grin");
        command("say ���е�Ҫ��������޷��ˣ�ƴ��һ������ס����");
        tell_object(me, HIC "��ѧ���ˡ���Ѫ�񵶡���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/xue", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/shi", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��ҿ�����ô��������Ѫ���ŵĵ����أ�";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "����Ѫ���󷨶�ûѧ��������ʲô��";

        if( query("family/gongji", me)<2000 )
                return "����Ϸ�������£��Ϸ���Ȼ�ᴫ�������";

        if( query("shen", me)>-100000 )
                return "����������ô���ģ���ɱ�˶������ˣ�";

        if (me->query_skill("force") < 250)
                return "����ڹ���Ϊʵ��̫����������������Ϸ�ɡ�";

        if( query("max_neili", me)<2600 )
                return "������������������Ȼ������˼�����Ϸ�";

        if (me->query_skill("xuedao-daofa", 1) < 180)
                return "�����Ѫ�����������������Ϸ�";

        message_vision(HIY "$n" HIY "����$N" HIY "��Ц��������˵�������벻����Ȼ��ô"
                       "�����\n���ܹ��̳�����һ�У���Ѫ�������Ǻ�����˰��������ұ�"
                       "��\n����ʽ����Ѫ�ԡ����������������䣬�漴ֻ��$n" HIY "��\n"
                       "��һ������������Ѫ��һ�񣬶�ʱ�ŷ�������Ѫ�⣬�����ޱ�\nɱ��"
                       "���쵶��������â��չ������һ���޴��Ѫ��$n" HIY "\n��������"
                       "�У�����֮������ʵ������������\n" NOR, me, this_object());

        command("haha");
        command("say ����������Ѫ���к�һ���������С����Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���Ѫ�ԡ���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/shi", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_midao()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "Ѫ����" )
                return "�������̵ģ����ֹ�������Ҫ˵ʲô��";

        command("whisper"+query("id", me)+"���Ȼ�Ѿ�������������"
                "����\nҪȥ��ԭ���£�����������Ѫ���ȱ������µ��ܵ�����"
                "�ɵ�ɽ\n������Ѵ�����(" NOR + HIY "enter mash" NOR + WHT
                ")��Ȼ����ܵ�����ԭ���ݡ�����\n������Ѫ��������ԭ������"
                "���ӿ�������" NOR + HIR "Ѫ���ޱ�" NOR + WHT "��\n");
        return "�����ܲ���й¶�����ˣ������������";
}

mixed ask_dao()
{
        object me;
        object ob;
        object owner;
int cost;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "Ѫ����" )
                        message_vision(CYN "$N" CYN "��ŭ����$n" CYN "����������"
                                       "Ϊ��Ѫ���ŵ��ӣ�����ѧ����ʼ������ˣ���"
                                       "Ȼ����������Ҫ����֮������\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��ŭ����$n" CYN "�ȵ�������"
                                       "��ʲô�ˣ���Ȼ��̰ͼ���������������ʿ���"
                                       "�������㣡��\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "Ѫ����" )
                return "Ѫ������Ѫ�������������������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ�����Ѫ�����㻹���Լ���ȥ�����ɡ�";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "��Ϊ��Ѫ����Ч��������������ӵ���㹻��ʦ�Ź��������һ�Ѫ��ʹ��ʱ��ɡ�";
        if( query("shen", me)>-50000 )
                return "��а�����أ�ʹ�ò���Ѫ����";

        ob = find_object(XUEDAO);
        if (! ob) ob = load_object(XUEDAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�����̵ģ����ŵ�Ѫ�����ڲ���������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ����Ѫ�����ڲ��������С�";

                if( query("family/family_name", owner) == "Ѫ����" )
                        return "Ѫ��������ʱ����ͬ��ʦ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "���ŵ�Ѫ����������"+query("name", owner)+
                               "���У���ȥ�������ˣ���Ѫ����������";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "����һЦ�������ã���ͽ�������Ѫ�����"
                       "��ȥ����ɱ����������ʿ���������ǵ����磡\n" NOR,
                       this_object(), me);
        command("give xuehun shendao to "+query("id", me));
addn("family/gongji", -cost, me); 
        ob->start_borrowing();
        return 1;
}

mixed ask_book()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "Ѫ����" )
                return "��������Ұ�֣����Ҵ���Ѫ���ŵ����⣿";

        if( query("family/master_id", me) != query("id") )
                return "���ֲ����Ϸ�ĵ��ӣ����Ϸ�����Щʲô��";

        if( query("shen", me)>-50000 )
                return "�㵹��ѧ����ʼ������ˣ����Ϸ�����������㣿";

        if( query("combat_exp", me)<300000 )
                return "�����ھ���̫ǳ���ⱾѪ�����㻹��������";

        if (me->query_skill("xuedao-daofa", 1) > 179)
                return "���Ѫ���󷨻���Ѿ������ˣ�Ѫ������������ʲô���á�";

        ob = find_object(JING);
        if (! ob) ob = load_object(JING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "��Ѫ���ŵı����������������ڿ���";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���š�Ѫ�������ڲ��������";

                if( query("family/family_name", owner) == "Ѫ����" )
                        return "Ѫ����������ʱ����ͬ�ŵ�"+query("name", owner)+
                               "ȡȥ���ˣ���Ҫ����ȥ�����ɡ�";
                else
                        return "��Ѫ���ŵı�������������"+query("name", owner)+
                               "���У���ȥ����������ɣ�";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "��ͷ�����ⱾѪ���������ȥ���ɣ���Ҫ��ϸ�Ķ���\n" NOR,
                       this_object(), me);
        // command("give xuedao book to " + me->query("id"));
        ob->move(me, 1);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != XUEDAO)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��������");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
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

        case "�ұػ�֮" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuedao-daofa/huan",
                           "name"    : "�ұػ�֮",
                           "sk1"     : "xuedao-daofa",
                           "lv1"     : 1000,
                           "sk2"     : "blade",
                           "lv2"     : 1000,
                           "reborn"  : 1, 
                           "gongxian": 8000, ]));
                break;
        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/
