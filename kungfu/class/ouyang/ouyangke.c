// ouyangke.c

#include <ansi.h>
#include "ouyang.h"

inherit F_MASTER;
inherit NPC;

void greeting(object ob);
int  accept_object(object who, object ob);
void do_back();
string ask_shenshe(string name);
string ask_job();
void reward_dest(object obj,object ob);
void destroy_dest(object obj,object ob);
void destroy_staff(object obj,object ob);
void thank_dest(object obj,object ob);

void create()
{
        seteuid(getuid());
        set_name("ŷ����", ({ "ouyang ke", "ouyang", "ke" }));
        set("long", "��һ��Ʈ�ݵİ�ɫ��������ҡ���ȣ��������š�\n");
        set("title", "ŷ��������ׯ��");
        set("nickname", "��������");
        set("gender", "����");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 25);
        set("int", 29);
        set("con", 25);
        set("dex", 26);

        set("qi", 1700);
        set("max_qi", 1700);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 50);

        set("combat_exp", 300000);

        set_skill("cuff",  130);
        set_skill("dodge", 120);
        set_skill("parry", 140);
        set_skill("force", 130);
        set_skill("staff", 100);
        set_skill("training", 80);
        set_skill("hamagong",130);
        set_skill("chanchu-bufa", 120);
        set_skill("lingshe-quan", 130);
        set_skill("baibian-daxue", 120);
        set_skill("poison", 120);
        set_skill("finger", 100);
        set_skill("shedu-qiqiao", 120);
        set_skill("medical", 150);
        set_skill("baituo-michuan", 150);
        set_skill("literate", 150);
        set_skill("shexing-diaoshou", 150);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff",  "lingshe-quan");
        map_skill("parry", "baibian-daxue");
        map_skill("staff", "baibian-daxue");
        map_skill("shedu-qiqiao", "shedu-qiqiao");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("ŷ������", 6, "����");

        set("inquiry", ([
                "��·����"   : (: ask_shenshe, "shenshe" :),
                "ŷ����" : "�������常��",
                "��ʬ��" : "��ֻ��һ�ݻ�ʬ�ۣ����ܸ��㡣������Ҫ�Ǹ���һ��ʬ�壬�ҿ��Ը�����Щ��",
                "��" : (: ask_job :),
                "job" : (: ask_job :),
        ]));

        set("chat_chance", 2);
        set("chat_msg", ({
                "ŷ���˳�����Ư���������������������Ҷ࿴��һ�ۣ���\n",
                "ŷ����ɫ���Եؿ��Žֱߵ�С���\n",
                "ŷ���˰�ֽ��һչ��ת����ȥ�����������������֪�����ѵã�\n",
        }) );

        set("master_ob",3);
        setup();
        carry_object("/d/baituo/obj/baipao")->wear();
        add_money("silver",10);
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        if (check_family(ob, "ŷ������"))
        {
                command("nod"+query("id", ob));
                return;
        }

        if( query("gender", ob) == "Ů��" )
        {
                if( query("per", ob)<22 )
                        return;

                if( query("sex/ŷ����", ob) )
                {
                        command("kiss"+query("id", ob));
                        command("say ��ô����Ҫ��Ҫ�������ΰ�... ������");
                } else
                switch(random(3))
                {
                case 0: command("rose "+(string)query("id", ob));break;
                case 1: command("kiss "+(string)query("id", ob));break;
                case 2: command("love "+(string)query("id", ob));break;
                }

        }
        else
                say("ŷ����̾��һ����˵����λ"+RANK_D->query_respect(ob)+
                        "����Ҫ���ܸ���Ūһ��Ů�����ͺ��ˡ�\n");
        return;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        message_vision("$N������... �ܺã�\n", this_object());
        command("recruit "+query("id", ob));
        if( !query("special/shenshe", ob) )
        {
                command("say �㻹����ʹ����·���߰ɣ��Ҹ�����ھ�����ɲ�Ҫ�����ˣ�");
                command("whisper"+query("id", ob)+"�ھ��ǣ�@#$%^&*����"
                        "������·���ߵ�������ɳĮ�Ϳ��������ߴ���ؼ��ˣ�");
                set("special/shenshe", 1, ob);
        }
}

int accept_fight(object ob)
{
        if( query("gender", ob) == "Ů��" )
        {
                message_vision("ŷ���˰ڰ���˵������λ"+RANK_D->query_respect(ob)+
                "���������۸�Ů�����أ�\n", ob);
                return 0;
        }

        return ::accept_fight(ob);
}

void do_back()
{
        remove_call_out("do_back");
        if (base_name(environment()) == query("startroom"))
                return;

        if (! living(this_object()) ||
            is_busy() || is_fighting())
        {
                call_out("do_back", 10 + random(10));
                return;
        }

        message_vision("$N��ҡ���ȣ�ƮȻ��ȥ��\n", this_object());
        move(query("startroom"));
        message_vision("$N��ҡ���ȣ�ʩʩȻ�����˹�����\n", this_object());
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

        message_vision("ŷ���˸�$Nһ��"+query("name", ob)+"��\n",this_player());
        return "�������˱�ɽׯ���У��мǲ��ɸ������ˣ�";
}

string ask_job()
{
        mapping job_stat;
        object ob2;
        object ob = this_player();
        object me = this_object();
        object guaishe,staff,here=environment(me);
                string dataname;
        int good_skill;

                dataname=query("id", ob);

        job_stat=query_temp("baituo/feeding", ob);

        if( query("family/family_name", ob) != "ŷ������" )
                return RANK_D->query_rude(ob)+"Ī�Ǳ������ģ�\n";

        if( query_temp(dataname, me)>5 )
                       return "���Ѿ�����Ҫ����ֻ���˶���û�����ң������ڲ����ĸ����ߣ���ȥ�侲һ�°ɡ�\n";


        if( ob->is_busy() ){
                command("hmm"+query("id", ob));
                return "�㻹��æ�Ÿɱ�����أ�\n";
        }

        if( job_stat ){
                command("hmm"+query("id", ob));
                return "�㻹û�������!\n";
        }

        if( ob->query_skill("training") < 10 && random(4)!=0 ) {
                return "���ѱ����̫�ͣ������ֻ������ȥ�ɡ�\n";
        }

        ob->start_busy(random(4));
        good_skill=to_int(pow(to_float(query("combat_exp", ob)/100),1.0/3))*10*0.7*3/2;

        if( query("combat_exp", ob)>20000 && (ob->query_skill("force")<good_skill) && random(15)>0){
                command("say ��ȥ�ú���ϰһ�¸�󡹦�ɣ�");
                return "��󡹦�Ǳ��ɵĶ��ž���������֮��һ�����԰ﱾ��ү��ץ������Ů����\n";
                }

        if( query("combat_exp", ob)>5000 && 
        query("max_neili", ob)<ob->query_skill("force")*7 && random(5)>0){
                command("say ������������ȥ�úô���һ�°ɣ�");
                return "����Խ�ߣ���󡹦��������Խ�󣬺ٺڣ�����ü��һ��Ҳ������\n";
                }



        if( query_temp("job_pos", me) == 0){
                if(random(8)==1)
                set_temp("job_pos", 1, me);
                return "����ûʲô�£����Ը����ε�ȥ�ɡ�\n";
        }

        addn_temp("job_pos", -1, me);
                addn_temp(dataname, 1, me);

        command("nod");
        command("say�ã���������һֻ�涾�Ĺ��ߣ�"+query("name", ob)+"����ȥ�úõ�����");
        command("say ����߳����ࡢ����Ѫ��Խ����ν�������ɵĸ��ֵ���ѪԽ���������ߡ�");
        command("hehe");
        command("say ���Ա����Ժ󣬾ͻ�ԹԵ������������Ϊ�����������ı�����");


        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        ob2 = new("/d/baituo/npc/guaishe");
        ob2->move(me);
        ob2->set_owner(ob);
        set_temp("baituo/feeding", 1, ob);
        addn("bt/job", 1, ob);
        set("bt/time", time(), ob);
        command("giveguaisheto"+query("id", ob));
        guaishe = present("guai she",me );
        if(guaishe)command("drop guai she");

        staff = present("guai shezhang",here);
        if(!staff)staff=present("guai shezhang",ob);
        if(staff)destruct(staff);
        staff = new("/clone/weapon/gshezhan");
        staff->move(me);
        command("giveguaishezhangto"+query("id", ob));
        guaishe = present("guai shezhang",me );
        if(guaishe)command("drop guai shezhang");

        return "ǧ���Ū���ˣ�\n";
}

int accept_object(object me, object obj)
{
        object obn;
        int addition;
        object hsf, ob = this_player();

        if( query("id", obj) == "corpse" )
        {
                if( !query("family", me) || query("family/family_name", me) != "ŷ������"){
                        command("say ��Ҫ�Ҹ�����ʬ���ɣ�\n");
                        return 0;
                }
                if( query("family/master_name", me) != "ŷ����" && 
                        query("family/master_name", me) != "ŷ����"){
                        command("say �㻹?������ù���ɡ�\n");
                        return 0;
                }

                if( query_temp("huashifen", me)){
                         command("say ��ʬ���������Ե�ҩ�ﲻҪ�õù��ࡣ\n");
                        return 0;
                 }

                message_vision("$N��" + obj->name() + "���ڵ��ϣ��ӻ����ͳ�һ�ݻ�ʬ���������档\n",this_object());
                message_vision("Ƭ��֮�䣬" + obj->name() + "����һ̲��ˮ����ˮ���˺����һ�ѷ���ӫӫ�Ļƹ�ķ�ĩ��\n" ,obj);
                message_vision("$N������һ�����ڻ��У�����Ľ���$n��\n",this_object(),me);
                command("say ����԰ѻ�ʬ�۵���ʬ���ϣ��ɼ��̽����ڻ�����");
                command("say ��Ҳ���԰���Ϳ�ڱ����ϸ�����װ���ˣ��������������˿ڣ����������ˡ�");
                command("hehe ouyang ke");

                hsf = new(DRUG_D("huashi"));
                hsf->set_amount(10);
                hsf->move(me);
                set_temp("huashifen", 1, me);
                return 1;
        }

        command( "say "+obj->name()+"?");

        if( query("id", obj) == "guaishe"){
                call_out("destroy_dest", 1, obj, ob);
                return 1;
        }

        if( query("id", obj) == "guaishezhang"){
                if( query("family/family_name", ob) == "ŷ������"){
                        if( query("snake", obj)>0 )
                                call_out("reward_dest", 1, obj, ob);
                        else
                                call_out("destroy_staff", 1, obj, ob);
                }
                else {
                        call_out("thank_dest", 1, obj, ob);
                }
                return 1;
        }

        if( !obj->is_character() || query("gender", obj) != "Ů��" )
        {
                      command("say ��ŷ���˲���Ҫ���������");
                return 0;
        }

        if( query("born_family", obj) == "ŷ������" )
        {
                command("kick"+query("id", me));
                command("slap"+query("id", me));
                command("say �ҿ����㵨�ӿ��治С�����ҵİ�����Ҳ���۸���");
                return 1;
        }

        if( query("short", environment(this_object())) == "����Ժ" )
        {
                       command("say ���Ѿ���Ů���ˣ�������������ɡ�");
                return 0;
        }

        if( query("age", obj)<18 )
        {
                command("fear");
                command("say δ������Ů������Ҫ��");
                return 0;
        }

        if( query("age", obj)>29 )
        {
                command("say �����ϹŶ������������Լ��ɣ�");
                return 0;
        }

        addition = 0;
        addition+=query("per", ob);
        if (userp(obj))
        {
                command("papapa");
                command("say ������С����ô���һ�ɫ�����Ů�Ļ������Լ����Űɣ�");
                return 0;
        }

        if( query("sex/ŷ����", obj) >= 3 )
        {
                command("shake");
                command("say ��Ů�����Ѿ������ˣ����Ը����Űɡ�");
                return 0;
        }

        if( !query("sex", ob) )
        {
                command("say �ۣ��⻹�Ǹ���Ů����ôҲ�ö��"
                        "�������ѣ�");
                addition += 30;
        }

        obn=new("/clone/money/silver");
        obn->set_amount(20 + addition);
        obn->move(me);

        message_vision("$n��" + obj->name() + "������$N��\n",
                       this_object(), me);

        message_vision("$Nһ�Ѱ�" + obj->name() + "���ڻ����$n˵��"
                       "����������������ѣ��ۻ�ͷ����\n˵�꣬��Я��" +
                       obj->name() + "������Ժ��ȥ...\n",
                       this_object(), me);

        obj->move("/d/city/lichunyuan");
        move("/d/city/lichunyuan");

        message_vision("$N���Ż��Բ��ѵ�$n���˽�����\n", this_object(), obj);

        addn("sex/ŷ����", 1, obj);
        addn("sex/times", 1, obj);
        if( query("sex/times", obj) == 1 )
                set("sex/first", "ŷ����", obj);

        obj->revive();
        tell_object(obj, HIY "��ո������۾���ȴ����һ����"
                        "�������㣬����һ�����������˹�ȥ��\n\n" NOR);
        command("kiss"+query("id", obj));
        command("say ���������ʲôô�����" + me->name() +
                "�����͹����İ���");
        /*
        shout(sprintf(HIW "\n%s(%s)����������������... ��... ����...\n\n" NOR,
                      obj->name()+HIW,query("id", obj)));
        */

        if (! userp(obj))
        {
                set("chat_chance", 15, obj);
                obj->set("chat_msg",({
                        obj->name() + "��ס�ĳ�����\n",
                        obj->name() + "���ʵ���" + this_object()->name() + "����... ��... �������������\n",
                        obj->name() + "�����������Ҳ�����ˣ�\n",
                }) );
        }

        remove_call_out("do_back");
        call_out("do_back", 10 + random(10));
        return -1;
}

void reward_dest(object obj,object ob)
{
        string dataname;

        dataname=query("id", ob);

        command("pat"+query("id", ob));
        command("say"+query("name", ob)+"�ɵĻ�����������ɻ��������үһ��������ģ�\n");

        if( query("gender", ob) == "Ů��" )
                command("kiss1"+query("id", ob));

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        addn_temp(dataname, -1, this_object());

                if( query_temp(dataname, this_object())<1 )
                {
                        delete_temp(dataname, this_object());
                }

                destruct(obj);
}


void destroy_staff(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say ��ô�����������ң����أ�С����ү������һ���ȣ�" );
        command( "angry" );

        destruct(obj);
}

void destroy_dest(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say ��ô�����������ң�Ӧ��ι����������ٽ����ҡ�С����ү��������߳ԣ�" );
        command( "angry" );

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        destruct(obj);
}


void thank_dest(object obj,object ob)
{
        command( "ah");
        command( "jump");
        command( "say ����ү�����ȣ���л����\n");
        destruct(obj);
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
                        ([ "perform" : "can_perform/shedu-qiqiao/da",
                           "name"    : "���־�",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "neili"   : 2000,
                           "gongxian": 200,
                           "shen"    : -4000, ]));
                break;

        case "����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedu-qiqiao/liandu",
                           "name"    : "����",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "neili"   : 2000,
                           "gongxian": 300,
                           "shen"    : -6000, ]));
                break;

        default:
                return 0;
        }
}

