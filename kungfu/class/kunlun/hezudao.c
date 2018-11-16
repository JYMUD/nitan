#include <ansi.h>
#include "kunlun.h"

#define LIANGJI    "/clone/lonely/liangjijian"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER; 

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_jian();

void create()
{
        object ob;
        set_name("�����", ({"he zudao", "he", "zudao"}));
        set("title", "�����ɿ�ɽ��ʦ");
        set("nickname", HIY "������ʥ" NOR);
        set("long", @LONG
����������ɿ�ɽ��ʦ���ų��ٽ�����������
����ʥ�����������������Ŀ����Ŀ���㡣ȴ
���ݹ����⣬����һ������
LONG);
        set("gender", "����");
        set("age", 95);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 4000000);

        set_skill("force", 600);
        set_skill("kunlun-xinfa", 600);
        set_skill("liangyi-shengong", 600);
        set_skill("dodge", 600);
        set_skill("chuanyun-bu", 600);
        set_skill("strike", 600);
        set_skill("kunlun-zhang", 600);
        set_skill("hand", 600);
        set_skill("sanyin-shou", 600);
        set_skill("cuff", 600);
        set_skill("zhentian-quan", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("kunlun-jian", 600);
        set_skill("xunlei-jian", 600);
        set_skill("zhengliangyi-jian", 600);
        set_skill("qiankun-jian", 600);
        set_skill("throwing", 600);
        set_skill("kunlun-qifa", 600);
        set_skill("tanqin-jifa", 600);
        set_skill("jian-jia", 600);
        set_skill("qiuyue-lai", 600);
        set_skill("tieqin-yin", 600);
        set_skill("chess", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "qiankun-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("strike", "kunlun-zhang");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "jian-jia");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("hand", "sanyin-shou");

        create_family("������", 1, "��ʦ");

        set("inquiry", ([
                "����"      : "��Ҫ��ʲô���У�",
                "����"      : "��Ҫ��ʲô������",
                "Ǭ����"    : (: ask_skill1 :),
                "����Ǭ��"  : (: ask_skill2 :),
                "��תǬ��"  : (: ask_skill3 :),
                "�����ɽ"  : (: ask_skill4 :),
                "������"    : (: ask_jian :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ni" :),
                (: perform_action, "sword.riyue" :),
                (: perform_action, "strike.kong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                ob = find_object(LIANGJI);
                if (! ob) ob = load_object(LIANGJI);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob=new(WEAPON_DIR"changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        /*
        if (clonep())
        {
                ob=new(WEAPON_DIR"treasure/jiaowei-qin");
                if (ob->violate_unique())
                {
                        destruct(ob);
                        ob=new(WEAPON_DIR"changjian");
                }
                ob->move(this_object());
                set_temp("handing", carry_object(ob));
        }
        */
        carry_object("/d/kunlun/obj/pao2")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<10000 )
        {
                command("say ��ѧ֮����ó�Զ��Ҫ��Ϊ��֮�����Ĵ�������"
                        "�л�����λ��");
                command("say ���Ǽ����󱲲������򣬵�ȴϣ��"
                        + RANK_D->query_respect(me) + "���ܹ����ע�⡣");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("sigh");
                command("say ��Ľ�������̫ǳ���Ҿ��������㣬������Ҳ��"
                        "������Ϊ��");
                return;
        }

        if (me->query_int() < 38)
        {
                command("say ������书�Լ�����ļ��ն������Լ��ߵ��˲�"
                        "���������У����±������ۡ�");
                command("say �ҿ�" + RANK_D->query_respect(me) + "����"
                        "�Ȼ�ȥ�������ɡ�");
                return;
        }

        if ((int)me->query_skill("liangyi-shengong", 1) < 100)
        {
                command("say ��ϰ�ҵ��书����������ǿ�������Ϊ����");
                command("say �ҿ�" + RANK_D->query_respect(me) + "�Ƿ�"
                        "��Ӧ�����ڱ��ŵ��ڹ��϶��µ㹦��");
                return;
        }

        if ((int)me->query_skill("zhengliangyi-jian", 1) < 100)
        {
                command("say ���ɵ������ǽ���������һ�������ҿ�"
                        + RANK_D->query_respect(me) + "�Դ˻���"
                        "�ò�����");
                return;
        }

        command("say ������Ҳ���������ˣ��Ҿͽ���һЩ�ٽ����֪ʶ�ɡ�");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/qian", me) )
                return "�ף������㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "����Ǭ���񽣶�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<300 )
                return "��Ա����������Ĺ��ײ�������һ������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 150)
                return "����ڹ�����㣬ѧ������һ�У�";

        if (me->query_skill("qiankun-jian", 1) < 100)
                return "���Ǭ������Ϊ���������Լ���ȥ���������ɡ�";

        message_vision(HIY "$n" HIY "΢΢һЦ��ת���������ȡ��һ��"
                       "������ָ������һ�ζ�$N" HIY "ϸ˵\n���ã�$N"
                       HIY "һ����һ�ߵ�ͷ��\n" NOR, me, this_object());
        command("nod");
        command("say ���������������Ľ���������ǿ������ȥ���Լ���ϰ��ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�Ǭ��������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/qian", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/riyue", me) )
                return "�ף������㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "����Ǭ���񽣶�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<1500 )
                return "��Ա����������Ĺ��ײ�������һ������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 220)
                return "����ڹ�����㣬ѧ������һ�У�";

        if (me->query_skill("qiankun-jian", 1) < 150)
                return "���Ǭ������Ϊ���������Լ���ȥ���������ɡ�";

        message_vision(HIY "$n" HIY "���˵�ͷ�������ҽ����и�����ʾһ"
                       "�飬��ɿ����ˡ�$n" HIY "��\n�����䣬ֻ������"
                       "��һչ����ָ������ָ��΢������Ǭ����������ʩ��"
                       "\n����$N" HIY "��ʱֻ����Ӱ���أ�ֱ�����ۻ���"
                       "�ҡ�\n" NOR, me, this_object());
        command("nod");
        command("say ���������Ǭ�����㿴���˶��٣�");
        tell_object(me, HIC "��ѧ���ˡ�����Ǭ������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/riyue", 1, me);
        addn("family/gongji", -1500, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/ni", me) )
                return "�ף������㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "����Ǭ���񽣶�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<1800 )
                return "��Ա����������Ĺ��ײ�������һ������ʱ�����ܴ��㡣";

        if( !query("can_perform/qiankun-jian/qian", me) )
                return "Ҫѧ���У�������ͨ����Ǭ�������İ��ء�";

        if (me->query_skill("force") < 300)
                return "����ڹ�����㣬ѧ������һ�У�";

        if (me->query_skill("qiankun-jian", 1) < 180)
                return "���Ǭ������Ϊ���������Լ���ȥ���������ɡ�";

        message_vision(HIW "$n" HIW "΢Ц������Ȼ��Ľ����Ѿ����ﳬ����"
                       "���磬�����Ҿʹ������С�\n$n" HIW "˵�š�ˢ����"
                       "һ���죬�ӱ��������ٵ��³��һ�������������\nǰ"
                       "��������Ȼ���䵯��������ֱ��$N" HIW "�ؿڣ�����"
                       "֮������Ϊ�κν�����\n������$N" HIW "��ʱ���ֲ�"
                       "����������������ȫ��֪�������Ӧ�С�$n" HIW "��"
                       "\n��һЦ�����𳤽���˵�����ղ���һ�в���ֱ�̣�ȴ"
                       "���Ⱦ�������Ȼ��\n�����������תǬ���İ��ر���"
                       "��Ǭ����������ʩչ���ɡ�\n" NOR, me,
                       this_object());
        command("haha");
        command("say ��������Ǭ���񽣵ľ��裬����ȥ���Լ��ڼ���ϰ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���תǬ������\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("liangyi-shengong"))
                me->improve_skill("liangyi-shengong", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/ni", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/kunlun-zhang/kong", me) )
                return "�ף������㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("kunlun-zhang", 1) < 1)
                return "���������Ʒ���ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<600 )
                return "��Ա����������Ĺ��ײ�������һ������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 150)
                return "����ڹ�����㣬ѧ������һ�У�";

        if (me->query_skill("kunlun-zhang", 1) < 120)
                return "��������Ʒ���Ϊ���������Լ���ȥ���������ɡ�";

        message_vision(HIY "$n" HIY "���˵�ͷ����$N" HIY "����"
                       "��ߣ��ڶ��Ե���ϸ˵���ã�$N" HIY "��"
                       "����ĵ�\nһЦ��������������\n" NOR, me,
                       this_object());
        command("nod");
        command("say �ղ�����˵�ı��������ɽ�ľ�Ҫ����ɼ����ˣ�");
        tell_object(me, HIC "��ѧ���ˡ������ɽ����\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("kunlun-zhang"))
                me->improve_skill("kunlun-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kunlun-zhang/kong", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "������" )
                return "���������ͱ��ɲ���ԨԴ���ι��������ҵ�����֮�";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ����ʸ�ʹ���ҵ������������»�����ذɡ�";

        if (me->query_skill("qiankun-jian", 1) < 150)
                return "���㽣�����֮�գ�����Ȼ������ϧ�彣��������ȥ�����ɡ�";

        if (me->query_skill("tanqin-jifa", 1) < 120
           && me->query_skill("chess", 1) < 120)
                return "���������ô�ã��ٺ���ȴ����㡭����";

        if (query("family/gongji", me) < 500)
                return "��Ϊʦ�������Ĺ��׻��������ⱦ�����ܸ���ʹ�á�";

        ob = find_object(LIANGJI);
        if (! ob) ob = load_object(LIANGJI);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ҵ��彣������������������Ϊ�λ��������������ˣ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "�������ˣ��ҵ����������ڲ����������С�";

                if( query("family/family_name", owner) == "������" )
                        return "�ҵ��彣������ʱ����ͬ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�ҵ��Ǳ�����������������"+query("name", owner)+
                               "���У���ȥ�����һ����ɡ�";
        }
        ob->move(this_object());
        command("give liangji jian to "+query("id", me));
        addn("family/gongji", -500, me);

        ob = new("clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        return "��Ȼ����������������������ʱ��ȥ�ðɡ�";
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != LIANGJI)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��л��λ" + RANK_D->query_respect(me) +
                        "���ҵı������ء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}

void init()
{
        object ob;

        if (interactive(ob = this_player())
           && ! is_fighting() && random(10) < 3)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        command("play jian-jia");
        return;
}
