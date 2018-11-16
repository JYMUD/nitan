#include <ansi.h>;

#define MOJIAN    "/clone/lonely/mojian"

inherit NPC;

mixed ask_jian();
mixed ask_skill1();
mixed ask_skill2();

void create()
{
        object ob;
        set_name("ʯ��", ({ "shi qing", "shi", "qing"}));
        set("gender", "����");
        set("title", "��������ׯׯ��");
        set("nickname", HIW "����˫��" NOR);
        set("age", 37);
        set("long", @LONG
����ǽ�������ׯׯ��ʯ�壬���ڽ���������
���ã�Ϊ�˺������塣ֻ���������ʣ�����
ƮƮ���������һ��������
LONG );
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 31);
        set("con", 33);
        set("dex", 31);

        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 180);
        set("combat_exp", 2200000);
        set("score", 25000);

        set_skill("force", 220);
        set_skill("wuwang-shengong", 220);
        set_skill("sword", 220);
        set_skill("shangqing-jian", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("strike", 220);
        set_skill("piaoxu-zhang", 220);
        set_skill("parry", 220);
        set_skill("literate", 250);
        set_skill("martial-cognize", 180);

        map_skill("force", "wuwang-shengong");
        map_skill("sword", "shangqing-jian");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "shangqing-jian");
        map_skill("strike", "piaoxu-zhang");

        prepare_skill("strike", "piaoxu-zhang");

        set("inquiry", ([
                "ī��"   : (: ask_jian :),
                "������" : (: ask_skill1 :),
                "������" : (: ask_skill2 :),
                "����"   : "�������µ����ӣ�������������",
                "������" : "�ҿ�Ƿ��ʵ��̫�࣬ʵ��̫�ࡣ",
                "������" : "�������������������������ںų������书��һ������������˫��",
                "����" : "��������������������֮�ӣ��ųơ����������������������˵á�",
                "ʯ����" : "�������µ�Ȯ�ӣ����Ӳ��ϣ��Һ޲�������ɱ������",
                "������" : "����������д�������뵽л�̿�Ϊ���������¡�",
                "л�̿�" : "л�̿ͱ��ǡ�Ħ���ʿ�����������ɢ����������ö��",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhuo" :),
                (: perform_action, "sword.qing" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        if (clonep())
        {
                ob = find_object(MOJIAN);
                if (! ob) ob = load_object(MOJIAN);
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

        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 50);
}

int recognize_apprentice(object ob, string skill)
{
        if( interactive(ob) && (!query("family", ob) || 
           query("family", ob)["master_name"] != "������") )
        {
                command("hmm");
                command("say ʯĳ���������ԨԴ����̸���ڶ��֣�\n");
                return -1;

        }

        if( query("shen", ob)<10000 )
        {
                command("heng");
                command("say ��ʯĳ���ܽ���ʦ�Ľ������������ֽ�����С��");
                return -1;
        }

        if (skill != "shangqing-jian" && skill != "sword")
        {
                command("shake");
                command("say ��ֻ�������彣����һЩ�����Ľ���֪ʶ������ȥ����"
                        "ʦ��ѧ�ɡ�");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("hmm");
                command("say ��Ľ��������Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�");
                return -1;
        }

        if( !query_temp("can_learn/shiqing", ob) )
        {
                command("sigh");
                command("say �������ҿ�Ƿ��ѩɽ��ʵ��̫�࣬���������׽���Ҳ��"
                        "Ӧ�õġ�");
                set_temp("can_learn/shiqing", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/shangqing-jian/zhuo", me) )
                return "���и��²����Ѿ���������";

        if( query("family/family_name", me) != "������" )
                return "ʯĳ���������ԨԴ����֪�����⻰�Ӻζ�����";

        if (me->query_skill("shangqing-jian", 1) < 1)
                return "�������彣����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "�ţ�����ѩɽ���еĵ�λ�����������Ҵ�����һ�С�";

        if( query("shen", me)<15000 )
                return "ѧ��֮�ˣ���Ӧ�Ե���Ϊ�ȡ��������������ò����������Ҳ��ܴ��㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����̫ǳ���ò�����һ�У�";

        if (me->query_skill("shangqing-jian", 1) < 140)
                return "�����彣����δ�����þ��û�������С�";

        message_vision(HIY "$n" HIY "΢΢һЦ���ӻ�������ȡ����һ��"
                       "���ף�ָ������һ�ζ�$N" HIY "ϸ\n˵���ã�$N"
                       HIY "һ����һ�ߵ�ͷ��\n" NOR, me, this_object());

        command("nod");
        command("say �ղ�����˵��ȫ�����еľ������ڣ�����ȥ�������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("shangqing-jian"))
                me->improve_skill("shangqing-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shangqing-jian/zhuo", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/shangqing-jian/qing", me) )
                return "���и��²����Ѿ���������";

        if( query("family/family_name", me) != "������" )
                return "ʯĳ���������ԨԴ����֪�����⻰�Ӻζ�����";

        if (me->query_skill("shangqing-jian", 1) < 1)
                return "�������彣����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<1600 )
                return "�ţ�����ѩɽ���еĵ�λ�����������Ҵ�����һ�С�";

        if( query("shen", me)<30000 )
                return "ѧ��֮�ˣ���Ӧ�Ե���Ϊ�ȡ��������������ò����������Ҳ��ܴ��㡣";

        if( !query("can_perform/shangqing-jian/zhuo", me) )
                return "��������������ͨ����������������ѧ���аɡ�";

        if (me->query_skill("force") < 220)
                return "����ڹ�����̫ǳ���ò�����һ�У�";

        if (me->query_skill("shangqing-jian", 1) < 160)
                return "�����彣����δ�����þ��û�������С�";

        message_vision( HIY "$n" HIY "����һЦ����$N" HIY "Ц������û��"
                        "��������ѩɽ�ɣ�ȴ���������\n�Ľ���������˳�"
                        "���뻯��ʯĳ���ձ㴫�����к��ˡ���ֻ��$n" HIY
                        "\n˵�꣬�㿪ʼ��������ʾ���У���˷��������顣"
                        "$N" HIY "��һ����ϸ��\n����������һЦ���ƺ�"
                        "������ʲô��\n" NOR, me, this_object());
        command("nod");
        command("say �ղ�����ʾ����ͼ������𣿼����˾��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("shangqing-jian"))
                me->improve_skill("shangqing-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shangqing-jian/qing", 1, me);
        addn("family/gongji", -1600, me);
        return 1;
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "������" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "�������ٸ�������ǰ˵�����ģ�С������ѩ"
                                       "ɽ�������������࣡��\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "��������ʲô��ͷ����Ȼ�Ҵ���ʯĳ���佣"
                                       "����\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "������" )
                return "ʯĳ������ز���ʶ����֪�����޹ʴ������µ��佣����Ϊ�Σ�";

        if( query("family/master_id", me) != "baizizai" )
                return "�ߣ���ƾ��Ҳ��Ҫʯĳ���佣��Ҫ������ʦ�����ɣ�";

        if( query("shen", me)<30000 )
                return "ѧ��֮�ˣ���Ӧ�Ե���Ϊ�ȡ��ҵ��佣���������ˣ����߰ɡ�";

        if (me->query_skill("shangqing-jian", 1) < 150)
                return "ī��ֻ�����������۵Ľ���������ʾ���������㽣�����ú������ɡ�";

        ob = find_object(MOJIAN);
        if (! ob) ob = load_object(MOJIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ţ�ʯĳ��ī����������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�����ҵ��佣�Ѿ��ñ���ȡȥ�ˡ�";

                if( query("family/family_name", owner) == "������" )
                        return "�ҵ��佣����ѩɽ�ɵ�"+query("name", owner)+
                               "ȡȥ�ˣ���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�ҵ��佣��"+query("name", owner)+
                               "ȡȥ�ˣ���ȥ�����ɣ�";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "̾�������ҵ��佣����ȥ�ðɣ���"
                       "�м����߽�����һ��һ����Ϊ�أ���\n" NOR,
                       this_object(), me);
        command("give mo jian to "+query("id", me));
        return 1;
}
