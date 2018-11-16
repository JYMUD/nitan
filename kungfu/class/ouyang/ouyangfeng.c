// ouyangfeng.c

#include <ansi.h>
#include "ouyang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

//#define ZHANG "/d/baituo/obj/lingshezhang"
#define ZHANG "/clone/lonely/lingshe"

string ask_shenshe(string name);
mixed ask_me();
mixed ask_music_book();
mixed ask_skill1();
mixed ask_skill2();
string ask_lingshe();
mixed ask_shegu();

void create()
{
        set_name("ŷ����", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "�����ǰ���ɽׯ�����ųơ���������ŷ���档����������\n"
                    "�����⺷����Ȼ�ܵ�������ƭ��ѧϰ�ˡ������澭������\n"
                    "����ħ��һ�ȱ�þ�����ң�����������Ȼ�ָ���������\n"
                    "ʤ������\n");
        set("title", "�������ɽׯ��");
        set("gender", "����");
        set("age", 53);
        set("nickname", HIR "����" NOR);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 32);
        set("int", 34);
        set("con", 34);
        set("dex", 32);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);

        set("combat_exp", 4000000);

        set_skill("force", 640);
        set_skill("strike", 640);
        set_skill("dodge", 640);
        set_skill("parry", 640);
        set_skill("cuff", 640);
        set_skill("finger", 640);
        set_skill("staff", 640);
        set_skill("training", 640);
        set_skill("poison", 640);
        set_skill("shedu-qiqiao", 640);
        set_skill("hamagong", 640);
        set_skill("chanchu-bufa", 640);
        set_skill("lingshe-quan", 640);
        set_skill("lingshe-zhangfa", 640);
        set_skill("shentuo-zhang", 640);
        set_skill("baibian-daxue", 640);
        set_skill("guzheng-jifa", 620);
        set_skill("xiyu-tiezheng", 620);
        set_skill("wushe-qu", 620);
        set_skill("literate", 680);
        set_skill("medical", 660);
        set_skill("baituo-michuan", 660);
        set_skill("jinchan-tunyue", 660);
        set_skill("martial-cognize", 620);
        set_skill("shexing-diaoshou", 660);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("strike","hamagong");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("ŷ������", 5, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qianshe" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "����"     : (: ask_me :),
                "����"     : (: ask_me :),
                "ǧ�߳���" : (: ask_me :),
                "��·����" : (: ask_shenshe, "shenshe":),
                "����"     : (: ask_lingshe :),
                "�߹�"     : (: ask_shegu :),
                "����"     : (: ask_music_book :),
                "���ݼ���" : (: ask_music_book :),
                "���߲���" : (: ask_skill1 :),
                "�����޼�" : (: ask_skill2 :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("music_book", 1);

        set("master_ob",5);
        setup();
        carry_object(__DIR__"obj/baipao")->wear();
        carry_object("/d/baituo/obj/shezhang")->wield();
        carry_object("d/baituo/obj/tiezheng");
        add_money("silver", 50);
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "guzheng-jifa")
                return 0;

        if( query_temp("can_learn/ouyang/guzheng-jifa", me) )
                return 1;

        command("say �ðɣ���Ը��ѧ�Ҿʹ���һ�����֮����");
        set_temp("can_learn/ouyang/guzheng-jifa", 1, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                if (random(2))
                        command("smile");
                else
                        command("pat"+query("id", ob));

                command("say ��ľ��黹�������Ⱥ��ҵ�ֶ��ŷ����ѧϰ�书�ɡ�");
                return ;
        }

        command("sigh");
        command("pat"+query("id", ob));
        command("recruit "+query("id", ob));
        command("say ����������ŷ�����Ǻ�����ˡ�");
        return;
}

mixed ask_skill1()
{
        object me=this_player();

        if( query("can_perform/lingshe-zhangfa/chan", me) )
                return "�Ҳ����Ѿ��̸�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("������ҰС�Ӹ���������Ұ��\n");

        if (me->query_skill("lingshe-zhangfa",1 ) < 100)
                return ("����ȷ��������ң�ѧ���ˡ����߲�����\n");

        command("say �ðɣ��㿴���ˡ�");
        tell_object(me, HIR"ŷ���彫�����߲���������һ�飬������ĬĬ���ǣ����о�̾���ѡ�\n"NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/chan", 1, me);
        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/lingshe-zhangfa/wuji", me) )
                return "�㻹����ȥ����ȥ���úð�����ŷ���ҷ�����";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("������ҰС�Ӹ���������Ұ��\n");

        if (me->query_skill("lingshe-zhangfa", 1) < 100)
                return ("����ȷ��������ң�ѧ���ˡ������޼ɡ���\n");

        command("say �ðɣ��㿴���ˡ�");
        tell_object(me, HIR"ŷ���彫�������޼ɡ�������һ�飬������ĬĬ���ǣ����о�̾���ѡ�\n"NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/wuji", 1, me);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/lingshe-zhangfa/qian", me) )
                return "�㻹����ȥ����ȥ���úð�����ŷ���ҷ�����";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����Ķ����ģ�����ô��";

        if( query("shen", me)>-40000 )
                return "�������ֶβ����ݶ��������ڻ����ܴ�����У�";

        if (me->query_skill("lingshe-zhangfa", 1) < 120)
                return "���Ⱥúð������ȷ���������˵��";

        message_vision(HIY "$n" HIY "�ȵ�������ϸ�ˣ�˵�ѵ�"
                       "�ۺ�ɨ�����������������Ǳ�������$N"
                       HIY "���۾�����ֱ�ˡ�\n" NOR,
                       me, this_object());
        command("heihei");
        command("say ����ʾ����ô������㿴����û�У�");
        tell_object(me, HIG "��ѧ����ǧ�߳�����\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
           set("can_perform/lingshe-zhangfa/qian", 1, me); 
        return 1;
}

string ask_shenshe(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "ŷ������" )
                return RANK_D->query_respect(this_player()) +
                "���㲢���Ǳ�ɽׯ���ˣ��˻��Ӻ�˵��";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "�����ϲ�������������ô����Ҫ������̰�����ᣡ";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("ŷ�����$Nһ��"+query("name", ob)+"��\n",this_player());
        return "�������˱�ɽׯ���У��мǲ��ɸ������ˣ�";
}

mixed ask_music_book()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "�ҵ������Ѿ����ȥ�ˡ�\n";

        ob = new("/clone/book/zhengpu");
        ob->move(me, 1);
        message_vision("$n�����׸���$N����������ȥ�Լ��ú���ĥ�ɡ�\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

mixed ask_shegu()
{
        object me, staff;
        object owner;
        object ob;
int lv,cost;
        me = this_player();

        if( query("family/family_name", me) != "ŷ������" && query("combat_exp", me)>100000){
                command("sneer"+query("id", me));
                command("say ����ɽ�߹ȵ����ܣ�����͸¶������֪����"+RANK_D->query_rude(me)+"����̫�����ˣ�");
                kill_ob(me);
                command("performbite"+query("id", me));//hasweapon
                command("performpuji"+query("id", me));//noweapon
                return 1;
        }

        if( query("family/family_name", me) != "ŷ������"){
                command("sneer"+query("id", me));
                message_vision("$Nû�лش�$n��\n", this_object(), me);
                return 1;
        }

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "��Ϊ�Ұ���ɽЧ��������������ӵ���㹻��ʦ�Ź��������һ�������ʹ��ʱ��ɡ�";
             ob = find_object(ZHANG);
             if (! ob) ob = load_object(ZHANG);
             owner = environment(ob);
             while (owner)
            {
                    if (owner->is_character() || ! environment(owner))
                            break;
                    owner = environment(owner);
            }

            if (owner == me)
                    return "�����Ȳ������������ô����ô���������أ�";

             if (objectp(owner) && owner != this_object())
             {
                     if (! owner->is_character())
                             return "���Ѿ����������Ѿ����ȥ�ˡ�";

                     if( query("family/master_id", owner) == query("id") )
                             return "������������"+query("name", owner)+
                                    "���У���Ҫ���þ�ȥ�����ɡ�";
                     else
                             return "��������������"+query("name", owner)+
                                    "���У���ȥ�����һ����ɡ�";
            }

        if( query("baituo/shegu_permit", me)){
//                command("say �߹��е��߶�����������Ⲷ׽���ú�����������ĪҪ����������������");
//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

message_vision("$N���ͷ�����߹��е��߶�����������Ⲷ׽���ú�����������ĪҪ����������������\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
addn("family/gongji", -cost, me); 
                ob->start_borrowing();
                return 1;
        }

        lv = (int)me->query_skill("poison", 1);

        if( lv < 80 ) {
                command("say ƾ�����ʹ�����£�����߹Ȼ���úܡ��ԹԵ���ׯ��������");
                return 1;
        }

        if( lv < 100 ) {
                command("pat "+query("id", me));
                command("say ��Ķ������е����ˣ���������߹ȣ����ö��µ㹦����ĥ��");
                return 1;
        }

        command("nod "+query("id", me));
        command("say ���ö������ͣ��ƺ��ǽ������ˡ��ã��Ϸ��������߹��������졣");
        set("baituo/shegu_permit", 1, me);

//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

//        message_vision("$N��һ��"+staff->name()+"����$n��\n",this_object(), me);
message_vision("$N���ͷ�����ӽ����ᣬ��������ɽ����߹ȡ����Ĵ������У���Ķ��������Ը��ϲ�¥��\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
//        command("say �ӽ����ᣬ��������ɽ����߹ȡ����Ĵ������У���Ķ��������Ը��ϲ�¥��");

        return 1;
}


string ask_lingshe()
{
        mapping fam;
        object obj, me;

        me = this_player();
        if( query("family/master_name", me) != "ŷ����"){
                return ("���޹������������Ǳ�ҪΪ�");
        }
        if (query("lingshe_count") < 1) {
                return ("����ѱ�����ף�����û�У�");
        }
        message_vision(CYN"$N�鴽��Х�����л����γ�һ����ɫС�ߣ�����$nҡͷ��β������ʾ���ʺá�\n"NOR,
        this_object(), me);
        obj = new("/d/baituo/npc/lingshe.c");
        obj->move(environment());
        addn("lingshe_count", -1);
                  return ("�������ԣ����޲��������Ƿ���Ե��Ϊ�������ˡ�");
}

void reset()
{
        if (query("lingshe_count") < 3)
                addn("lingshe_count", 1);
        set("music_book", 1);
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/zhen",
                           "name"    : "������",
                           "sk1"     : "hamagong",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : -24000, ]));
                break;

        case "����˻�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/puji",
                           "name"    : "����˻�",
                           "sk1"     : "hamagong",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : -28000, ]));
                break;

        case "����ʽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/tui",
                           "name"    : "����ʽ",
                           "sk1"     : "hamagong",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 400,
                           "shen"    : -20000, ]));
                break;

        case "ѩ��ǧɽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shentuo-zhang/suo",
                           "name"    : "ѩ��ǧɽ",
                           "sk1"     : "shentuo-zhang",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-quan/rou",
                           "name"    : "���־�",
                           "sk1"     : "lingshe-quan",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baibian-daxue/dian",
                           "name"    : "���־�",
                           "sk1"     : "baibian-daxue",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        case "���߲���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-zhangfa/chan",
                           "name"    : "���߲���",
                           "sk1"     : "lingshe-zhangfa",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -30000, ]));
                break;

        default:
                return 0;
        }
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHANG)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��л��λ" + RANK_D->query_respect(me) + "���������ͻء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}
