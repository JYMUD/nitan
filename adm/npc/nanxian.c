// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_NOCLONE;

#define CONTRACT        "/d/reborn/obj/contract"

mixed ask_me1();
mixed ask_me2();
mixed ask_me3();
mixed ask_me4();
mixed ask_me5();
mixed ask_me6();
mixed ask_reborn();
mixed ask_buchang();
mixed ask_duanwu();
int full_all();

void create()
{
        set_name("����", ({ "nan xian", "nan", "xian" }));
        set("long", @LONG
����������ɼ���뷢�԰ס�������ò���ʵ
ȴΪ����ͷ���������������кųơ�����
���󡹵����͡���Ϊ��������а������ʱ����
�����������춯�صĴ�١���ƽ��ս��������
�ڱ�������ʧ���֡�
LONG);
        set("nickname", HIW "��������" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 74);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "name" : "����������һ�ִ��Ŷ��ѣ������к����壿",
                "����" : "�㾡���Ǹ������ļһ�������",
                "״̬�ظ�": (: full_all :),
                "״̬�ָ�": (: full_all :),
/*
                "��̶" : (: ask_me1 :),
                "����" : (: ask_me1 :),
                "gift" : (: ask_me1 :),
*/
                "��Ч����": (: ask_me2 :),
                "˫������": (: ask_me3 :),
                "����"    : (: ask_me4 :),
                "������": (: ask_me4 :),
                "��ɽ����": (: ask_me4 :),
                "�μӱ���": (: ask_me4 :),
                "������Ա": (: ask_me5 :),
                "������Ա����": (: ask_me5 :),
                "������Ա�ȼ�": (: ask_me5 :),
                //"���ֵ�ʦ����Ʊ": (: ask_me6 :),
                "ת������" : (: ask_reborn :),
                "ת��" : (: ask_reborn :),
                "����" : (: ask_reborn :),
                "ת��" : (: ask_reborn :),
                //"����" : (: ask_buchang :),
  		//"�����" : (: ask_duanwu :),

        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        /*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(WHT "\nͻȻ������ǰһ��������ƺ����˸�"
                               "��Ӱ��\n" NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
        */
        set("startroom", "/d/city/wumiao");
        check_clone();
}

void init()
{
/*
        object ob; 
        ::init();

        if (interactive(ob = this_player()) && ! is_fighting()) 
        if (interactive(ob = this_player()) && ! is_fighting() && ! query("welcomegift", ob)) 
        {
                remove_call_out("greeting"); 
                call_out("greeting", 1, ob); 
        }
*/
}

void greeting(object ob) 
{
        if ( ! ob || environment(ob) != environment() ) return; 
        say( CYN "����΢΢һЦ������λ" + RANK_D->query_respect(ob) + CYN + "�����˰ɣ��������и������͸���(ask nan xian about ����)��\n" NOR); 
}

// ����ѯ��
mixed accept_ask(object who, string topic)
{
        object me;
        object ob_hlp;
        int i;

        me = this_player();

        if (topic == "Ѱ�ҵ�����ͼ")
        {
                //if (! me->query("reborn/times")) return "�㻹û�о���ת���������޷���ȡ����\n";
/*
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "�Բ��𣬵�����ͼ����ֻ�����Ч��Ա���ţ�\n";
*/
                if( query("quest_tuteng/end", me) )
                        return "��������������ȴ�����͵���Ը����л��\n";
                if( query("quest_tuteng/start", me) )
                        return "���Ѿ���ȡ�˸������뾡���Ѽ����ŵ�����ͼ�����Ұɣ�\n";
                if( query("balance", me)<100000000 )
                        return "�������(bank)���㣬��ȡ��������Ҫ֧��1�����ƽ�\n";

                addn("balance", -100000000, me);
                set("quest_tuteng/start", 1, me);

                return "�ðɣ����ȥѰ�ҵ�����ͼ�ɡ�\n";
        }

        if (topic == "�������")
        {
                string *spks = ({
                        "zhuque",
                        "tianshen",
                        "qijin",
                        "taxue",
                });
                int n;
                string mapsk;

                // ����Ƿ�����Ч��Ա
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "�Բ��𣬵�����ͼ����ֻ�����Ч��Ա���ţ�\n";
                // ����Ƿ���ȡ������
                if( !query("quest_tuteng/start", me) )
                        return "�Һ���û�н���������ɡ�\n";
                // ��������Ƿ������
                if( query("quest_tuteng/end", me) )
                        return "��������������ȴ�����͵���Ը����л��\n";

                if (me->query_skill("badao", 1) > 0 && me->query_skill("badao", 1) < 600)
                        return "���¼Ȼ�Ե�������ϰ��������������ϰһ��ʱ�������ɣ������ʧ������\n";

                // ����Ƿ����7�ŵ���ͼ
                for (i = 1; i <= 7; i ++)
                {
                        if (! objectp(ob_hlp = present("diwang futu" + sprintf("%d", i), me)))
                                return "��ô������Ҫ��7�ŵ���ͼ�Ѽ�������\n";

                        if (base_name(ob_hlp) != "/clone/tuteng/futu" + sprintf("%d", i))
                                return "��ô������Ҫ��7�ŵ���ͼ�Ѽ�������\n";
                }

                // ��ȫ���ݻ�7��ͼ
                for (i = 1; i <= 7; i ++)
                {
                        ob_hlp = present("diwang futu" + sprintf("%d", i), me);
                        destruct(ob_hlp);
                }

                // 1�����轱��--���SP2�����֣�
                //    ����Ѿ������SP2�ˣ��򲻻�ø�SP2�����ɻ�þ��齱��
                if( !query("quest_tuteng/end3", me) )
                {
                        set("special_skill/"+spks[random(sizeof(spks))], 1, me);
                        write("��ȡ���ͼ�ڼ��ܣ� \n");
                }

                // 2��exp 150��  pot 200 �� weiwang 100�� ���� 100��
                GIFT_D->delay_bonus(me,
                                    ([ "exp"      : 1500000,
                                       "pot"      : 2000000,
                                       "weiwang"  : 1000000,
                                       "score"    : 1000000,
                                       "prompt"   : "����ɵ�����ͼ����֮��"]), 999);

                // 3�����л������ܼ������ڻ�������֮�ϵļ��������ȴ�����������������һ����
                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("staff");
                if (me->can_improve_skill("staff"))
                        me->improve_skill("staff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("unarmed");
                if (me->can_improve_skill("unarmed"))
                        me->improve_skill("unarmed", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("sword");
                if (me->can_improve_skill("sword"))
                        me->improve_skill("sword", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("blade");
                if (me->can_improve_skill("blade"))
                        me->improve_skill("blade", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("finger");
                if (me->can_improve_skill("finger"))
                        me->improve_skill("finger", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("claw");
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("hand");
                if (me->can_improve_skill("hand"))
                        me->improve_skill("hand", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("strike");
                if (me->can_improve_skill("strike"))
                        me->improve_skill("strike", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("cuff");
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("whip");
                if (me->can_improve_skill("whip"))
                        me->improve_skill("whip", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                if (me->can_improve_skill("riding"))
                        me->improve_skill("riding", 15000000);

                if (me->can_improve_skill("martial-cognize"))
                        me->improve_skill("martial-cognize", 15000000);

                // 4����Ե��ȼ�����600lv�����ھ����ҰԵ�����5���ȼ��������ȣ����������5����
                if (me->query_skill("badao",1) >= 600)
                {
                        message_sort(HIC "\n���ͼ�����$N˵�������¼Ȼ�Ե������Ͳ��ţ�Ҳ��֪һ������ı������"
                                         "�������½���֪���㽲��һ�� ����\n" NOR, me);

                        tell_object(me, HIW "���������͵Ľ���󣬶԰Ե������µ���ᣡ\n" NOR);
                        tell_object(me, HIW "��ϲ�㣬ѧ���ˡ��۰����¡��������ǵ���һ������\n" NOR);
                        set("can_perform/badao/xiong", 1, me);
                        set("can_perform/badao/san-1", 1, me);
                        for (i = 0; i < 5; i ++)
                        {
                                if (me->can_improve_skill("badao"))
                                        me->improve_skill("badao", 15000000);
                        }
                        tell_object(me, HIM "�������Ķ���˵������˵��ֻҪ��Ե��ﵽ800�����Ⱒ�ǵ��ڶ�������������ѧϰ��\n" NOR);
                        tell_object(me, HIM "�����ֶ���˵������������������׽��㣬��Ҫ�ҵ����µ�һ���--�����������������\n" NOR);
                }
                // ����������ɱ�־
                set("quest_tuteng/end", 1, me);

                me->save();
                log_file("diwang-quest",query("id", me)+"��"+ctime(time())+"��ɵ�����ͼ����\n");

                return 1;
        }
        if (topic == "���޵�")
        {

                if( query("int", me)<32 || 
                    query("con", me)<32 || 
                    query("str", me)<32 || 
                    query("dex", me)<32 )
                    return "����������Ի��������������޵����ҿ��㻹���Ȼ�ȥ�ɡ�\n";
        
                if( query("reborn/times", me)<3 )
                        return "�ߣ�û�±������ң��߿���\n";
                
                if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                        return "�����书�Ѿ��������£���ϲ��ϲ��\n";                    

                if (me->query_skill("lunhui-sword",1))
                        return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                                
                // �Ѿ��������
                if( query("lunhui-sword_quest/xiuluodao/finish", me) && 
                    me->query_skill("xiuluodao", 1))
                        return "�Ǻǣ�������ϴΰ��ң����޵н������Ѿ������ɹ��ˡ�\n";
        
                // ��������
                if( !query("lunhui-sword_quest/xiuluodao/give_quest", me) )
                {
                        command("hehe");
                        command("say �������������챦��֮�޵н���������1�����������");
                        command("ke");
                        command("say �ܰ������æ��");
                        tell_object(me, this_object()->name() + HIG "��������Ѽ�1������ѣ��Ͽ�ȥ�ɣ�\n" NOR);
                        set("lunhui-sword_quest/xiuluodao/give_quest", 1, me);
                        me->save();
                        return "�³�֮���һᴫ�㼸���书����";
                }
                
                // �������
                
                if (! objectp(ob_hlp = present("qinggang jian", me)))
                        return "��ô����1������Ѽ�������\n";
                        
                if (base_name(ob_hlp) != "/clone/weapon/qinggang-jian")
                        return "��ô����1������Ѽ�������\n";

                destruct(ob_hlp);
                
                command("hehe");
                command("nod");
                command("say ��Ȼ����������æ���Ҿ�˳�㴫��һ�У��������Ժ��õ��� ...");
                
                message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                             "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                             "�Ըղŵ�������������\n", this_object(), me);
                                        
                tell_object(me, HIG "��ϲ�������ˡ����޵���������Ŀǰ�ȼ�Ϊ10����\n");
                me->set_skill("xiuluodao", 10);
                set("lunhui-sword_quest/xiuluodao/finish", 1, me);
                
                return "�����ˣ�";              
        }
        


        return ULTRA_QUEST_D->accept_ask(this_object(), who, topic);
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say �ߣ���֪���");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say û��Ȥ��");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("����밵�㣬������ǰһ��������̫�����\n");
}

mixed ask_me1()
{
        object me = this_player();
        object ob;

        if( query("welcomegift", me) )
        {
                command("say �Ǻǡ���������Ĳ����ˣ��Ϸ��Ѿ������������ˣ�");
                return 1;
        }
        else
        {
                set("welcomegift", 1, me);
                addn("food", 5000, me);
                addn("water", 10000, me);
                addn("score", 1000, me);
                addn("weiwang", 100, me);
                set("tianfu", 4, me);
                // me->add("potential", 1000);
                me->add_skill("training", 200);

                ob = new("/adm/npc/obj/gift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/zhenyu");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/longjia");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/xuanhuang");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                // ob->move(this_object());
                // command("give gift to " + me->query("id"));

                /*
                CHANNEL_D->do_channel(me, "es", sprintf("����%s���չ��١���̶����61.128.162.81 : 2001��\n            ���ѵõ����͵İ����ͽ�����������ʼ������ˣ�",
                                      me->name(1)));
                */

                message_vision(HIW "$N" HIW "���һָ��ͻȻ�����һ��" HIM "��" HIY "��" HIR "ϼ" HIC "��" HIW "����$n��ת˲���ţ�\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "�����͸�����һ�����gift��������� look gift ��������ʲô���\n" NOR);
                return 1;
        }
}

mixed ask_me2()
{
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day1", me) == td )
                return "������Ѿ������Ч��������ʱ���ˡ�";

        if (! MEMBER_D->is_valid_member(me))
        // || (int)MEMBER_D->db_query_member(me, "endtime") < 1888888888)
                return "�㲻�ǻ�Ա����Ҫ��Ч�������������ȹ����Ա���ɡ�\n";

/*
        message("member", HIM "\n����̶��Ա��" + me->query_idname() + HIM " ��ȡ��Сʱ�ĸ�Ч ���ʱ�俪ʼ��ʱ��\n" NOR,
                all_interactive(), 0);
*/

        tell_object(me, HIR "\n����ȡ��Сʱ�ĸ�Ч����ʱ�俪ʼ��ʱ������ָ��istat���Բ鿴ʣ��ʱ�䡣\n" NOR);

        addn("time_reward/study", 7200, me);
        set("time_reward/which_day1", td, me);
        return 1;
}

mixed ask_me3()
{
        // int t;
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day2", me) != td )
                delete("time_reward/times", me);

        if( query("time_reward/which_day2", me) == td &&
            query("time_reward/times", me) >= 3 )
                return "������Ѿ��������е�˫�����齱��ʱ���ˡ�";

        if (! MEMBER_D->is_valid_member(me))
                return "�㲻�ǻ�Ա����Ҫ˫�����齱�������ȹ����Ա���ɡ�\n";

        /*
        t = localtime(time())[2];
        if (t >= 20 && t < 24)
                return "ÿ��20~24���Ϊ˫������ʱ�䣬����������˫������ʱ����㻹�ǹ�һ��������ɡ�\n";

        message("member", HIM "\n����̶��Ա��" + me->query_idname() + HIM " ��ȡ��Сʱ��˫������ʱ�俪ʼ��ʱ��\n" NOR,
                all_interactive(), 0);
        */

        tell_object(me, HIR "\n����ȡ��Сʱ��˫������ʱ�俪ʼ��ʱ������ָ��istat���Բ鿴ʣ��ʱ�䡣\n" NOR);

        set("time_reward/which_day2", td, me);
        addn("time_reward/quest", 7200, me);
        addn("time_reward/times", 1, me);
        return 1;
}

mixed ask_me4()
{
        object me = this_player();

        tell_object(me, HIY "����˵������Ȼ��Ҫ�μӱ��䣬��ô�Ϸ������һ�̣�\n" NOR);
        message_vision(HIY "ֻ����������һ�У�һ���������$N��$N�ڿշ�ȥ��\n" NOR, me);
        me->move("/d/huashan/houzhiwangyu");
        return 1;
}

mixed ask_duanwu()
{
	object me = this_player();
	object ob;

	if (query_temp("duanwu_time", me) > time())
		tell_object(me, HIY "����˵����" + query("name", me)  + "��ո��Ѿ��ù��ˣ�������Ҫ�ȴ�10�룬ÿ����ÿ��ֻ�ܳ�һ��Ӵ��\n"NOR);
	else {
		tell_object(me, HIY "����˵����" + query("name", me)  + "����ڿ��֣�\n"NOR);
 		message_vision(HIY "���ʹӻ����ó�һ�������͸��� " + query("name", me) + "��\n" NOR);
		ob = new("/u/luoyun/zongzi");
		ob->move(me);
		set_temp("duanwu_time", time() +10, me);
	}
	 return 1;
}


int full_all()
{
        object me, ob;
        int max;

        me = this_object();
        ob = this_player();

        //ֻ���������ʺ�������30��������С��18��ĵ�ID
        if( time()-query("birthday", ob)>86400*19 )
        {
                command("say ���Ѿ����������ˣ���Ҫ�����չ����ѽ��\n");
                return 1;
        }

        max=query("max_jing", ob);
        ob->receive_curing("jing", max);
        ob->receive_heal("jing", max);
        max=query("max_qi", ob);
        ob->receive_curing("qi", max);
        ob->receive_heal("qi", max);
        max=query("max_neili", ob);
        set("neili", max, ob);
        max=query("max_jingli", ob);
        set("jingli", max, ob);
        set("food", ob->max_food_capacity(), ob);
        set("water", ob->max_water_capacity(), ob);
        ob->start_busy(2);
        message_vision(CYN "$N΢Ц�����ֳ�$nһ�������������ˣ���\n" NOR,me, ob);
        tell_object(ob, HIC "��ٸ���ĭ���磬������ˬ��ƣ����ȥ��\n" NOR);
        return 1;
}

mixed ask_me5()
{
        int value, trans, t;
        object me = this_player();

        t = time();
        if( !wizardp(me) && t-query_temp("identify_member", me)<10 )
                return "��ողż����������ǵȻ������ɡ�\n";

        if (! MEMBER_D->is_member(me))
                return "�㲻�ǻ�Ա����Ҫ������Ա�ȼ������ȹ����Ա���ɡ�\n";

        if (MEMBER_D->db_query_member(me, "vip") == 3)
                return "��ϲ�㣬���Ѿ��ǰ׽��Ա�ˣ�\n";

        set_temp("identify_member", t, me);

        value = MEMBER_D->db_query_member(me, "payvalue");
        trans = MEMBER_D->db_query_member(me, "transfervalue");
        value -= trans;

        if (value >= 2000)
        {
                MEMBER_D->db_set_member(me, "vip", 3);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ����׽��Ա�����Ա�̵깺��Ʒ���� 8 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 1000)
        {
                MEMBER_D->db_set_member(me, "vip", 2);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ���ƽ��Ա����Ա�̵깺��Ʒ���� 8.8 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 500 && MEMBER_D->db_query_member(me, "vip") < 2)
        {
                MEMBER_D->db_set_member(me, "vip", 1);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ�������Ա���Ա�̵깺��Ʒ���� 9.5 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        {
                if (MEMBER_D->db_query_member(me, "vip") == 2)
                        return "��Ŀǰ�Ļ�Ա�ȼ�Ϊ�ƽ��Ա��\n";

                if (MEMBER_D->db_query_member(me, "vip") == 1)
                        return "��Ŀǰ�Ļ�Ա�ȼ�Ϊ������Ա��\n";

                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ��ͨ��Ա��\n" NOR);
                return 1;
        }
}

mixed ask_me6()
{
        int wd;
        object me = this_player();

        wd = time() / 604800;

        if( query("flowers/which_week", me) == wd )
                return "�㱾���Ѿ�������ֵ�ʦ����Ʊ�ˡ�";

        if (! MEMBER_D->is_valid_member(me))
                return "�㲻�ǻ�Ա����Ҫ��ȡ���ֵ�ʦ����Ʊ�����ȹ����Ա���ɡ�\n";

        tell_object(me, HIR "\n����ȡ��һ�����ֵ�ʦ����Ʊ������ָ��flowers���Բ鿴��ӵ�е����ֵ�ʦ����Ʊ����\n" NOR);

        set("flowers/amount", 1, me);
        set("flowers/which_week", wd, me);
        return 1;
}

mixed ask_buchang()
{
        string id, sql;
        int    jointime, endtime, day;
        object me = this_player();
        object ob;


        if( query("gifter/buchang", me) )
                return "���Ѿ����������,��Ҫ̫̰��Ŷ��";

        id=query("id", me);

        if( !MEMBER_D->is_member(id) ) // �ǳ�ֵ�û��϶����ǻ�Ա
        {
                day = time() + 15724800; // ��������Ļ�Ա
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d",
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
                me->set_srv("quit_save", 86400*365); // 1���������Ʒ����
                ob = new("/clone/goods/washgift");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/goods/mask");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if( jointime < 1 ) jointime = time();

                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if( endtime < 1 )  // �ǻ�Ա
                {
                        day = time() + 15724800;  // ����Ļ�Ա
                        me->set_srv("quit_save", 86400*365);
                        ob = new("/clone/goods/washgift");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                        ob = new("/clone/goods/mask");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                }
                else
                {
                        // �Ƿ�С�����
                        if( endtime - jointime < 31536000 ||
                            query("online_time", me)<86400*3)//��ֹˢnt
                        {
                                if( endtime >= time() + 7948800 )
                                {
                                        log_file("buchang", sprintf("%s %s get buchang but the endtime is %d\n",
                                                                    TIME_D->replace_ctime(time()), id, endtime));
                                        endtime = time() + 7948800;
                                }

                                if( endtime > time() )
                                        day = endtime + 15724800; // ����Ļ�Աʱ��
                                else
                                        day = time() + 15724800;

                                me->set_srv("quit_save", 86400*365);
                                ob = new("/clone/goods/washgift");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                                ob = new("/clone/goods/mask");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                        }
                        else
                        {
                                // �Ƿ�����
                                if( endtime - jointime >= 63072000 )
                                {
                                        day = endtime;
                                        MEMBER_D->db_pay_member(id, 200); // ����200nt
                                        me->set_srv("quit_save", 86400*365);
                                }
                                else // �Ƿ����
                                {
                                        if( endtime > time() )
                                                day = endtime + 7948800; // 1�����ȵĻ�Աʱ��
                                        else
                                                day = time() + 7948800;

                                        MEMBER_D->db_pay_member(id, 70); // ����70nt
                                        me->set_srv("quit_save", 86400*365);
                                        ob = new("/clone/goods/washgift");
                                        ob->move(me, 1);
                                        set("no_sell", 1, ob);
                                        set("bindable", 3, ob);
                                        set("bind_owner", id, ob);
                                        set("auto_load", 1, ob);
                                        set("set_data", 1, ob);
                                }
                        }
                }
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }

        set("gifter/buchang", 1, me);
        me->save();
        tell_object(me, HIY "\n����ȡ��(" HIM "��������" NOR + HIY ")��ף��������֮ս�������죡\n" NOR);
        return 1;
}

mixed ask_reborn()
{
        object ob, who, weapon;
        string map_skill, type;

        who = this_player();

        if( query("reborn/times", who) >= 3 )
        {
                message_vision("$N��$nһ���֣����� ��Ѿ����������ֻ��ˣ��ҿ��Ͳ����˰ɣ�\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn_offer", who) )
        {
                message_vision("$N��$nŭ�����Ϸ��Ѿ�������һ��������(Contract)��Ϊ�λ������ң�\n",
                               this_object(), who);
                return 1;
        }

        if( (!query("reborn/times", who) && query("combat_exp", who)<6000000000) ||
            (query("reborn/times", who) == 1 && query("combat_exp", who)<10000000000) ||
            (query("reborn/times", who) == 2 && query("combat_exp", who)<20000000000) )
        {
                message_vision("$N��$nһ���֣��������鲻����ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        if( query("betrayer", who) )
        {
                message_vision("$N��$nŭ�����㻹���Ȱ�����ʦ�����еľ�������������\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("force");
        if (who->query_skillo("force", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N��$nһ���֣������ڹ�������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("dodge");
        if (who->query_skillo("dodge", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N��$nһ���֣������Ṧ������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("parry");
        if (who->query_skillo("parry", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N��$nһ���֣������мܲ�����ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        if (who->query_skillo("martial-cognize", 1) < 3600)
        {
                message_vision("$N��$nһ���֣�������ѧ����������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        weapon=query_temp("weapon", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/hands", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/finger", who);
        if( !weapon || /*!weapon->is_ultimate()*/ query("status", weapon) < 6 ||
            query("id", who) != weapon->item_owner() )
        {
                message_vision("$N��$nһ���֣����������ӵ��һ��Ʒ�������ı���������ת��������\n",
                               this_object(), who);
                return 1;
        }

        type=query("skill_type", weapon);
        if( type )
        {
                map_skill = who->query_skill_mapped(type);
                if (! map_skill)
                {
                        message_vision("$N��$nһ���֣�����������ȼ�������װ���ı�����Ӧ�ı������ܡ�\n",
                                        this_object(), who);
                        return 1;
                }
        }
        else
        {
                type = "unarmed";
                map_skill = who->query_skill_mapped(type);
                if( !map_skill ) { type = "strike"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "hand"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "cuff"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "finger"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "claw"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) {
                        message_vision("$N��$nһ���֣�����������ȼ�������װ���ı�����Ӧ�ı������ܡ�\n",
                                       this_object(), who);
                        return 1;
                }
        }

        if (who->query_skillo(type, 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N��$nһ���֣�����" + to_chinese(map_skill) + "������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        if (! ultrap(who))
        {
                message_vision("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if( !query("breakup", who) )
        {
                message_vision("$N��$nһ���֣������㻹û�д�ͨ���ζ������ء�\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("animaout", who) )
        {
                message_vision("$N��$nһ���֣������㻹û������ԪӤ�����ء�\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("death", who) )
        {
                message_vision("$N��$nһ���֣������㻹û�д�ͨ�����������ء�\n",
                               this_object(), who);
                return 1;
        }

        if( query("couple/couple_id", who) )
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���ļ�ͥ����������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if( query("bunch", who) )
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���İ�������������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if( query("brothers", who) )
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���Ľ����ֵ�����������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if( query("league", who) )
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ����ͬ������������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if( query("private_room", who) )
        {
                message_vision("$N��$nһ���֣������㻹���Ȱ����ס����ٵ���ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        message_vision(CYN "$N̾�������˼䱾�ǰ�׮ĥ����Ȼ������֮ʿ��ѯ���Ϸ�Ҳ����׾��������������°ɡ���\n" NOR,
                       this_object(), who);

        ob = new(CONTRACT);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("owner",query("id",  who), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        message_vision(HIC "$N�ó�һ��������(Contract)��$n��\n" NOR
                       CYN "$N������������ת����Ե����������ɽ���׼��������ǰ��̩ɽ����ɽ����ɽ����ɽ����ɽһ�аɡ���\n" NOR,
                       this_object(), who);

        message("channel:rumor",HBRED"��ת���������˼䣺"+query("name", who)+"("+query("id", who)+")"
                HBRED "�õ�����������ʼǰ�������׼�������ת����Ե��\n\n" NOR, users());

        set("reborn_offer", "start", who);

        return 1;
}

int accept_object(object who, object ob)
{
        int r;

        if (r = ULTRA_QUEST_D->accept_object(this_object(), who, ob))
                return r;

        if (base_name(ob) != CONTRACT ||
            query("owner", ob) != query("id", who) )
                return 0;

        if( sizeof(query("offer", ob))<5 )
                return notify_fail(CYN "����ҡҡͷ�����������׼�δ�ɣ�Ϊʱ���硣��\n" NOR);

        delete("bindable", ob);
        delete("bind_owner", ob);
        call_out("to_return", 1, who, ob);
        return 1;
}

int to_return(object who, object ob)
{
        if (! ob || ! who) return 0;

        message_vision(CYN "$N���˵�ͷ�����������������ˣ������߹�����ɽ���ǰ�������ĥ������������Ǹ�Ѫָӡ����\n" NOR
                       HIC "$n����$Nָʾ��ҧ��Ĵָ�����������ϸ���Ѫָӡ��\n" NOR
                       HIM "ֻ��������(Contract)ͻ���Ϲ⣬Ѫָӡ��ƾ���ֳ���$n�����֡�\n" NOR
                       CYN "$N����������ȥ����֮��Ѱ�����ؾ�����������Ͷ�����У����ɻ������������������֮�ʸ�·���ն����С�ġ���\n" NOR,
                       this_object(), who);

        set("name", MAG"������"NOR, ob);
        ob->set_name(MAG "������" NOR, ({ "contract" }));
        set("long", MAG"����һ��������������Ѫָӡ����"+who->query_idname()+"�����֡�\n"NOR, ob);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("reborn_offer", "finish", who);
        tell_object(who, HIC "���ͽ����Ϲ��������(Contract)�����㡣\n" NOR);

        return 1;
}

void unconcious()
{
        die();
}
