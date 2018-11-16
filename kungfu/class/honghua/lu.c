#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_jian();
mixed ask_zhen();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

#define BAILONG    "/clone/lonely/bailongjian"

void create()
{
        object ob;
        set_name("½����", ({ "lu feiqing", "lu", "feiqing" }));
        set("long", "½���࣬���䵱�ɴ�����׳��ʱ�ڴ��ϱ�\n"
                    "�������壬�˵����𽭺������������߽��\n"
                    "����½����Զ�߽߱�����ʱ��͢����������\n"
                    "׷�ã�����Ϊ�˻�������֮�书��ǿ������\n"
                    "���ѣ�����͢�����ϼӲ鼩��\n");
        set("nickname", HIW "������" NOR);
        set("gender", "����");
        set("class", "scholar");
        set("age", 62);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 23);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("combat_exp", 4000000);
        set("score", 500000);

        set_skill("force", 260);
        set_skill("taiji-shengong", 260);
        set_skill("unarmed", 240);
        set_skill("xuangong-quan", 240);
        set_skill("dodge", 240);
        set_skill("tiyunzong", 240);
        set_skill("sword", 240);
        set_skill("rouyun-jian", 240);
        set_skill("taiji-jian", 240);
        set_skill("parry", 240);
        set_skill("throwing", 240);
        set_skill("furong-jinzhen", 240);
        set_skill("martial-cognize", 220);
        set_skill("literate", 220);

        map_skill("force"  , "taiji-shengong");
        map_skill("sword"  , "rouyun-jian");
        map_skill("unarmed" , "xuangong-quan");
        map_skill("dodge"  , "tiyunzong");
        map_skill("parry"  , "taiji-jian");
        map_skill("throwing"  , "furong-jinzhen");

        prepare_skill("unarmed", "xuangong-quan");

        set("inquiry", ([
                "ܽ�ؽ���"   : (: ask_zhen :),
                "������"     : (: ask_jian :),
                "������Ӱ"   : (: ask_skill1 :),
                "��������"   : (: ask_skill2 :),
                "�����޼���" : (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xuan" :),
                (: perform_action, "sword.tao" :),
                (: perform_action, "throwing.xian" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        create_family("�䵱��", 17, "����");

        set("zhen_count", 3);

        setup();

        if (clonep())
        {
                ob = find_object(BAILONG);
                if (! ob) ob = load_object(BAILONG);
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
        set_temp("handing", carry_object("/d/kaifeng/npc/obj/jinzhen"));
}

void attempt_apprentice(object ob)
{
        command("sigh");
        command("say �Ҳ���ͽ����Ҫ��ʦ��ֱ��ȥ�䵱ɽ���ˡ�");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "�컨��" && 
           query("family/family_name", ob) != "�䵱��" )
        {
                command("hmm");
                command("say ƶ�����������ԨԴ����̸���ڶ��֣�\n");
                return -1;
        }

        if( query("family/family_name", ob) == "�䵱��" )
        {
                command("sigh");
                command("say ���Ѿ�˵���Ҳ���ͽ�ˣ���Щ�㻹��ȥ����ʦ��ѧ�ɡ�\n");
                return -1;
        }

        if( query("family/master_id", ob) != "chenjialuo" && 
           query("family/master_id", ob) != "wuchendaozhang" && 
           query("family/master_id", ob) != "zhaobanshan" )
        {
                command("say ƶ������²������죬����������ʦ��ѧȥ�ɡ�\n");
                return -1; 
        }

        if( query("shen", ob)<50000 )
        {
                command("hmm");
                command("say ����������컨��ĺú��������µĵ����ƺ�����ô����");
                return -1;
        }

        if (skill != "sword" && skill != "rouyun-jian" &&
           skill != "unarmed" && skill != "xuangong-quan" &&
           skill != "throwing" && skill != "furong-jinzhen")
        {
                command("shake");
                command("say ��ֻ������һЩ������ȭ�źͰ����Ĺ���������������ʦ��ѧ�ɡ�");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("say ��Ľ��������Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�");
                return -1;
        }

        if (skill == "unarmed" && ob->query_skill("unarmed", 1) > 179)
        {
                command("say ���ȭ�Ź����Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�");
                return -1;
        }

        if (skill == "throwing" && ob->query_skill("throwing", 1) > 179)
        {
                command("say ��İ����ַ��Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�");
                return -1;
        }

        if( !query_temp("can_learn/lufeiqing", ob) )
        {
                command("say ���ڴ�е�ǰ����Ҳ�˲����䵱�ɵ�ʲô�Ź��ˡ�");
                command("say �����ƽ������޼�����ȭ��ܽ�ؽ���������ƽ��ѧ���ʹ�������ˡ�");
                set_temp("can_learn/lufeiqing", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/furong-jinzhen/xian", me) )
                return "�Լ���ȥ�����̵ܽ��Ҷ������̸����ˡ�";

        if( query("family/family_name", me) != "�컨��" && 
           query("family/family_name", me) != "�䵱��" )
                return "ƶ�����������ԨԴ����֪�����⻰�Ӻζ�����";

        if (me->query_skill("furong-jinzhen", 1) < 1)
                return "����ܽ�ؽ��붼ûѧ����̸ʲô���п��ԣ�";

            if( query("family/gongji", me)<300 )
                return "�ţ����"+query("family/family_name", me)+CYN
                       "�����Ĺ��ײ����������Ҳ����㡣";

        if( query("shen", me)<30000 )
                return "�������������ò����������Ҳ��ܴ��㡣";

        if (me->query_skill("force") < 120)
                return "����ڹ�����㣬�ò�����һ�У�";

        if (me->query_skill("furong-jinzhen", 1) < 80)
                return "��ܽ�ؽ�����δ�����þ���������ô��С�";

        message_vision(HIY "$n" HIY "��$N" HIY "Ц��Ц�����������"
                       "�����һ�����룬���ᵯ������ʱֻ\n����쬡�"
                       "��һ�������뻯��һ����â��û��$N" HIY "��"
                       "��ǰ����ʯ�أ�ֻ��\n��һ��С�ס�\n" NOR,
                       me, this_object());

        command("nod");
        command("say Ҫ������ס����ʣ�¾Ϳ����Լ����ˡ�");
        tell_object(me, HIC "��ѧ���ˡ�������Ӱ����\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("furong-jinzhen"))
                me->improve_skill("furong-jinzhen", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/furong-jinzhen/xian", 1, me);
          addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/rouyun-jian/tao", me) )
                return "�����㲻���Ѿ�ѧ������";

        if( query("family/family_name", me) != "�컨��" && 
           query("family/family_name", me) != "�䵱��" )
                return "ƶ�����������ԨԴ����֪�����⻰�Ӻζ�����";

        if (me->query_skill("rouyun-jian", 1) < 1)
                return "�������ƽ�����ûѧ����̸ʲô���п��ԣ�";

            if( query("family/gongji", me)<700 )
                return "�ţ����"+query("family/family_name", me)+CYN
                       "�����Ĺ��ײ����������Ҳ����㡣";

        if( query("shen", me)<60000 )
                return "�������������ò����������Ҳ��ܴ��㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ�����̫ǳ���ò�����һ�У�";

        if (me->query_skill("dodge") < 180)
                return "����Ṧ��Ϊ�������ò�����һ�У�";

        if (me->query_skill("rouyun-jian", 1) < 140)
                return "�����ƽ�����δ�����þ���������ô��С�";

        message_vision(HIY "$n" HIY "΢΢һЦ���ӻ�������ȡ����һ��"
                       "���ף�ָ������һ�ζ�$N" HIY "ϸ\n˵���ã�$N"
                       HIY "һ����һ�ߵ�ͷ��\n" NOR, me, this_object());

        command("nod");
        command("say ��Щȫ�����������µľ������ڣ�����ȥ�������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ��������¡���\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("rouyun-jian"))
                me->improve_skill("rouyun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/rouyun-jian/tao", 1, me);
          addn("family/gongji", -700, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/xuangong-quan/xuan", me) )
                return "�������Ѿ��̹����ˣ��Լ���ȥ���ɡ�";

        if( query("family/family_name", me) != "�컨��" && 
           query("family/family_name", me) != "�䵱��" )
                return "ƶ�����������ԨԴ����֪�����⻰�Ӻζ�����";

        if (me->query_skill("xuangong-quan", 1) < 1)
                return "�����޼�����ȭ��ûѧ����̸ʲô���п��ԣ�";

            if( query("family/gongji", me)<400 )
                return "�ţ����"+query("family/family_name", me)+CYN
                       "�����Ĺ��ײ����������Ҳ����㡣";

        if( query("shen", me)<50000 )
                return "�������������ò����������Ҳ��ܴ��㡣";

        if (me->query_skill("force") < 160)
                return "����ڹ�����̫ǳ���ò�����һ�У�";

        if (me->query_skill("xuangong-quan", 1) < 120)
                return "���޼�����ȭ��δ�����þ���������ô��С�";

        message_vision(HIY "$n" HIY "���˵�ͷ����$N" HIY "����"
                       "��ߣ��ڶ��Ե���ϸ˵���ã�$N" HIY "��"
                       "�����\n��һЦ��������������\n" NOR, me,
                       this_object());

        command("nod");
        command("say �ղŵĻ��㶼������ˣ��Լ���ȥ�������ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������޼�������\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("xuangong-quan"))
                me->improve_skill("xuangong-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuangong-quan/xuan", 1, me);
          addn("family/gongji", -400, me);
        return 1;
}

mixed ask_zhen()
{
        object me;
        object ob;

        me = this_player();

        if (me->is_bad())
                return "����аħ�������������ƶ��������";

        if( query("family/family_name", me) != "�컨��" && 
           query("family/family_name", me) != "�䵱��" )
                return RANK_D->query_respect(me) + "��ƶ���ز���ʶ����֪"
                       "�˻��ν⣿";

        if (me->query_skill("furong-jinzhen", 1) < 80)
                return "��ܽ�ؽ�����ַ��������ң�����ܽ�ؽ���Ҳûʲô�á�";

        if (query("zhen_count") < 1)
                return "���ֲ���������ģ������������ô�ࡣ";

        addn("zhen_count", -1);
        ob = new("/d/kaifeng/npc/obj/jinzhen");
        message_vision("$N�ó���ʮ��" HIY "ܽ�ؽ���" NOR "(Furong jinzhen)��$n��\n",
                       this_object(), me);
        ob->move(me, 1);
        return "��Ȼ�������������ܽ�ؽ����������ȥ�ðɡ�";
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "�컨��" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "�������ٸ�������ǰ˵�����ģ�С�������"
                                       "���������������࣡��\n" NOR,
                                       this_object(), me);
                else
                if( query("family/family_name", me) == "�䵱��" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "���������䵱����Ϊȴ��˲��ܣ���������"
                                       "����ǰ˵�����ģ���\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "��������ʲô��ͷ����Ȼ�Ҵ���½ĳ���佣"
                                       "����\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) == "�䵱��" )
                return "�������ͬ���䵱�������佣��������֮��ִ�е�ǰ�����㽻�衣";

        if( query("family/family_name", me) != "�컨��" )
                return "ƶ��������ز���ʶ����֪�����޹ʴ������µ��佣����Ϊ�Σ�";

        if( query("family/master_id", me) != "chenjialuo" && 
           query("family/master_id", me) != "wuchendaozhang" && 
           query("family/master_id", me) != "zhaobanshan" )
                return "������ʦ�����죬����������ܽ����㡣";

        if( query("shen", me)<30000 )
                return "ѧ��֮�ˣ���Ӧ�Ե���Ϊ�ȡ��ҵ��佣���������ˣ����߰ɡ�";

        if (me->query_skill("rouyun-jian", 1) < 150)
                return "�㻹������ƶ����������ƽ�������֮����˵�ɡ�";

        ob = find_object(BAILONG);
        if (! ob) ob = load_object(BAILONG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ţ�ƶ���İ���������������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�����ҵ��佣�Ѿ��ñ���ȡȥ�ˡ�";

                if( query("family/family_name", owner) == "�䵱��" )
                        return "�ҵ��佣���������䵱����"+query("name", owner)+
                               "���У���Ҫ�þ�ȥ�����ɡ�";
                else
                if( query("family/family_name", owner) == "�컨��" )
                        return "�ҵ��佣�����Ǻ컨���"+query("name", owner)+
                               "ȡȥ�ˣ���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�ҵ��佣�����䵽��"+query("name", owner)+
                               "���У���ȥ�����ɣ�";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "̾�������佣����ȥ�ɣ����м�����"
                       "��������Ϊ�أ�Ī���˺컨�����������\n" NOR,
                       this_object(), me);
        command("givebailongjianto"+query("id", me));
        return 1;
}
