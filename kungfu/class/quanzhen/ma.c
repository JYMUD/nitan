// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();
string ask_miji();
mixed ask_skill1();
mixed ask_skill2();
string ask_array();
string ask_shu();
void create()
{
        set_name("����", ({"ma yu", "ma"}));
        set("gender", "����");
        set("age", 42);
        set("class", "taoist");
        set("nickname",MAG"������"NOR);
        set("long",
                "�������������Ĵ���ӣ�ȫ������֮�ף����������������ˡ�\n"
                "����ü��Ŀ���Ͱ����ף���Ц�ſ����㡣\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 30);

        set("title","ȫ������֮��");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4700);
        set("max_neili", 4700);
        set("jiali", 100);
        set("level", 18);
        set("combat_exp", 1400000);

        set_skill("force", 180);
        set_skill("quanzhen-xinfa", 180);
        set_skill("sword", 170);
        set_skill("quanzhen-jian",170);
        set_skill("dodge", 180);
        set_skill("jinyan-gong", 180);
        set_skill("parry", 180);
        set_skill("literate",100);
        set_skill("strike", 180);
        set_skill("chongyang-shenzhang", 180);
        set_skill("haotian-zhang", 180);
        set_skill("finger",180);
        set_skill("zhongnan-zhi", 180);
        set_skill("taoism",150);
        set_skill("medical", 210);
        set_skill("liandan-shu", 210);
        set_skill("cuff",200);
        set_skill("whip",200);
        set_skill("chunyang-quan",200);
        set_skill("duanyun-bian",200);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("ȫ���", 2, "����");

        set("book_count",1);
        set("miji_count",1);
        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
                "�ؼ�" : (: ask_miji :),
                "���㹦" : (: ask_me :),
                "����ͼ��" : (: ask_me :),
                "ӥ������" : (: ask_skill1 :),
                "�������" : (: ask_array :),
                "����������" : (: ask_array :),
                "�ؼ�"      : (: ask_shu :),
                "�޷��ܾ�"   : (: ask_shu :),
                "shu" : (: ask_shu :),
                "���Ž���" : (: ask_skill2 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/weapon/changjian");
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 100 )
        {
                command("say ��ı����ڹ��ķ������,�������Ը�������书��");
                return;
        }
        if( query("shen", ob)<10000 )
        {
                command("say ���������ұ�ѧ�������������ģ���������Ŀɲ�������\n");
                return;
        }
        command("pat"+query("id", ob));
        command("say �ðɣ��Ҿ����������ͽ���ˡ�");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "ȫ���" )
                return RANK_D->query_respect(this_player()) +
                "�뱾�̺��޹ϸ��ҽ̵��书�伮�ɲ��ܽ����㡣";
        if (query("book_count") < 1)
                return "�������ˣ�����ͼ���Ѿ�����ȡ���ˡ�";
        addn("book_count", -1);
        ob = new("/clone/book/jinyantu");
        ob->move(this_player());
        return "�ðɣ��Ȿ������ͼ�ס����û�ȥ�ú��ж���";

}
string ask_shu()
{
        object ob;

        if( query("family/master_id", this_player()) != "mayu" )
                return RANK_D->query_respect(this_player()) +
                "���ҵ��ӣ���֪�˻��Ӻ�̸��";
        if (query("shu_count") < 1)
                return "�������ˣ����ɵ��ؼ����ڴ˴���";
        addn("shu_count", -1);
        ob = new("/clone/book/whip");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"�õ��޷��ܾ�����\n");
        return "�ðɣ��Ȿ���޷��ܾ������û�ȥ�ú����С�";
}
string ask_miji()
{
        mapping fam;
        object ob, *obs,ob2 ;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "ȫ���" )
                return RANK_D->query_respect(this_player()) +
                "�뱾��������������֪�˻��Ӻ�̸��";

        if (query("miji_count") < 1)
                return "�������ˣ����ɵı޷��ؼ����ڴ˴���";

        obs = filter_array(children("/d/quanzhen/obj/whip_book"), (: clonep :));
                  if (sizeof(obs) > 5)
                return "�������ˣ����ɵı޷��ؼ����ڴ˴���";

        ob=new("/d/quanzhen/obj/whip_book");
        ob->move(this_player());
        addn("miji_count", -1);
        // command ("rumor "+this_player()->query("name")+"Ū����һ�ᵤ���޷��ס�");
        return "�ðɣ��Ȿ�������޷��ס����û�ȥ�ú����С�";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jinyan-gong/yanwu", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("jinyan-gong", 1) < 1)
                return "�������㹦��ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<50 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<3000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("jinyan-gong", 1) < 60)
                return "��Ľ��㹦������죬���ߵ������ɡ�";

        if (me->query_skill("force") < 80)
                return "����ڹ���Ϊ�����������ߺ��������Ұɡ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ�����¸�����"
                     "����������Ӱʱ��ӥ�����ա�ʱ��Ⱥ����裬������"
                     "�����ң�ɷ�Ǻÿ���\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say ���кܼ򵥣��Լ���ϰ��ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�ӥ�����衹��\n" NOR);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("jinyan-gong"))
                me->improve_skill("jinyan-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyan-gong/yanwu", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jinguan-yusuo/suo", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶ���ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("jinguan-yusuo", 1) < 1)
                return "�������������ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<400 )
                return "������ȫ�����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<50000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("jinguan-yusuo", 1) < 150)
                return "��Ľ������������죬���ߵ������ɡ�";

        if (me->query_skill("force") < 200)
                return "����ڹ���Ϊ�����������ߺ��������Ұɡ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ��˵�������Ҹ�����ʾһ�飬��"
                     "����ϸ�ˡ���ֻ��$n" HIY "�������䣬��ʱ���������˫"
                     "����Ļ�Ȧ�������������λ����$N" HIY "��ȥ����ʱ"
                     "$N" HIY "ֻ������һ��������˫��̱��ȫ���������Ʊ�"
                     "$n" HIY "��סһ�㡣\n\n" NOR, me, this_object()); 

        command("nod");
        command("say ���п��Ƽ򵥣�ʵȴ����ޱȣ����������ɡ�");
        command("say �պ����߽������мǵ����˴������ˣ�ĪҪ������");
        tell_object(me, HIC "��ѧ���ˡ����Ž�������\n" NOR);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("jinguan-yusuo"))
                me->improve_skill("jinguan-yusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinguan-yusuo/suo", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
string ask_array()
{
        object room, qizi, obj, ob = this_player(), me = this_object();
        mapping ob_fam, skl;
        string *skillname;
        int i;

        ob_fam=query("family", ob);
        skl = ob->query_skills();

        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(ob) +
                "���������������ʸ��������";
        if( query("score", ob)<20000 )
                return RANK_D->query_respect(ob) +
                "�������㣬�����ʸ��������";

        skillname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if ((skl[skillname[i]] < 80) || (sizeof(skl) == 0))
                return RANK_D->query_respect(ob) +
                "���������������ʸ��������";
        }
        if( query("qixing", ob) )
                return RANK_D->query_respect(ob) +
                "��Ȼ����������󣬿ɲ�Ҫ���ϵ��������Ц��";
/*
        if ( ob_fam["family_name"] != "ȫ���" || ob_fam["generation"] != 3)
                return RANK_D->query_respect(ob) + "����û�ʸ��������";
*/
        if( query("assigned_qixing", me) )
                return RANK_D->query_respect(ob) + "������������ս����������һ��ʱ�������ɡ�";

        set("assigned_qixing",query("id",  ob), me);
        command("smile");
        say("\n���ڵ���˵�����ðɣ���ȥ�ټ���ʦ�ܡ��Ժ��ڴ�У���ϵ��㡣\n");
        message_vision("\n���ڵ��������뿪��\n\n", ob);

/* ̷���� */
        if(!( room = find_object("/d/quanzhen/rongwutang")) )
                room = load_object("/d/quanzhen/rongwutang");
                  me->move(room);
        if( !objectp(obj = present("tan chuduan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹�������̷����˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "̷���˵��˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* ������ */
        if(!( room = find_object("/d/quanzhen/jingxiushi")) )
                room = load_object("/d/quanzhen/jingxiushi");
                  me->move(room);
        if( !objectp(obj = present("liu chuxuan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹�������������˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "���������˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �𴦻� */
        if(!( room = find_object("/d/quanzhen/laojundian")) )
                room = load_object("/d/quanzhen/laojundian");
                  me->move(room);
        if( !objectp(obj = present("qiu chuji", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹��������𴦻�˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "�𴦻����˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* ����һ */
        if(!( room = find_object("/d/quanzhen/wanwutang")) )
                room = load_object("/d/quanzhen/wanwutang");
                  me->move(room);
        if( !objectp(obj = present("wang chuyi", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹�����������һ˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "����һ���˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �´�ͨ */
        if(!( room = find_object("/d/quanzhen/guangning")) )
                room = load_object("/d/quanzhen/guangning");
                  me->move(room);
        if( !objectp(obj = present("hao datong", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹��������´�ͨ˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "�´�ͨ���˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �ﲻ�� */
        if(!( room = find_object("/d/quanzhen/qingjing")) )
                room = load_object("/d/quanzhen/qingjing");
                  me->move(room);
        if( !objectp(obj = present("sun buer", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n���ڵ������˹�����\n\n", ob);
                return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";
        }
        message("vision","\n���ڵ������˹��������ﲻ��˵�˼��䡣\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "�ﲻ�����˵�ͷ���첽���˳�ȥ��\n", room, obj);
        set_temp("pre_qixing", 1, ob);

        me->move("/d/quanzhen/daxiaochang");
        call_out("waiting", 1, me,1);
        return "�ã���Ҷ������ˡ�\n";
}

int waiting(object me,int wait_time)
{
        object ob;

        if( wait_time == 300 )
        {
                say( "����˵�����������������ˣ����ǻ�ȥ�գ�\n\n");
                call_out("do_back", 0, me);
                addn("score", -5000, ob);
        }
        else if( !objectp(ob=present(query("assigned_qixing", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me,wait_time);
        }
        else call_out("preparing", 0, me, ob);

        return 1;
}

int preparing(object me, object ob)
{
        object *obs, room, obj1, obj2, obj3, obj4, obj5, obj6;
        string myname=query("name", me);
        int i;

        if(!( room = find_object("/d/quanzhen/daxiaochang")) )
        room = load_object("/d/quanzhen/daxiaochang");
        if(!objectp( obj1 = present("tan chuduan", environment(me))))
                return notify_fail("��ʦ����ô���ڣ�\n");
        if(!objectp( obj2 = present("liu chuxuan", environment(me))))
                return notify_fail("��ʦ����ô���ڣ�\n");
        if(!objectp( obj3 = present("qiu chuji", environment(me))))
                return notify_fail("��ʦ����ô���ڣ�\n");
        if(!objectp( obj4 = present("wang chuyi", environment(me))))
                return notify_fail("��ʦ����ô���ڣ�\n");
        if(!objectp( obj5 = present("hao datong", environment(me))))
                return notify_fail("��ʦ����ô���ڣ�\n");
        if(!objectp( obj6 = present("sun buer", environment(me))))
                return notify_fail("Сʦ����ô���ڣ�\n");

        me->dismiss_team();
        me->set_leader();
        me->add_team_member(obj1);
        me->add_team_member(obj2);
        me->add_team_member(obj3);
        me->add_team_member(obj4);
        me->add_team_member(obj5);
        me->add_team_member(obj6);

        say( "����˵��������ɵ��ˣ��粻����Ħ��������뼴���뿪��\n");


  obs=me->query_team();
        for(i=0;i<sizeof(obs);i++)
        {
                ob->fight_ob(obs[i]);
                obs[i]->fight_ob(ob);
                if(obs[i] != me)
                        message_vision(myname+"����"+query("name", obs[i])+"������׼����\n",me);
        }
//        command("say chat " + ob->query("title") + ob->query("name") +
//                "�ڽ���" + NATURE_D->game_time() + "��սȫ���������\n");
        message("channel:snow",HIC"����������[Mayu]��"+query("title", ob)+query("name", ob)+
                HIC+"�ڽ���" + NATURE_D->game_time() + "��սȫ���������\n"NOR,users());
        say(HIC"������������һס���Ѽ�ʮ�ꡣ��\n");
        say("̷��������������ͷ��������ߡ���\n");
        say("������������������ͤ�������ӡ���\n");
        say("�𴦻��ӿڵ�������Ҷ����̫���ɡ���\n");
        say("����һ�������������������⡣��\n");
        say("�´�ͨ����������������δ��ǰ����\n");
        say("�ﲻ��������������һЦ�޾а�����\n");
        say("�����վ�������������������죡��\n\n\n"NOR);

        message_vision(myname+ "���������������˵�����ã�ʱ���ѵ������ڿ�ʼ������������󡹣�\n",me);
        message_vision(myname+ "ͻȻ�����ƶ���������ȫ�������ռλ�ã�������ˣ��ұ����ˣ����ǰڵġ���������󷨡�\n",me);
        say("����λ�����̷࣬����λ����诣�������λ�����ᣬ�𴦻�λ����Ȩ��������ɶ�����\n");
        say("����һλ����⣬�´�ͨλ���������ﲻ��λ��ҡ�⣬������ɶ�����\n");
        remove_call_out("do_qixing");
        call_out("do_qixing", 2, me, ob);
        return 1;
}


int do_qixing(object me, object en)
{
        object *obs, weapon, enweapon;
        int i, j, power;
        string err;
        string *where = ({
                "����",
                "���",
                "����",
                "��Ȩ",
                "���",
                "����",
                "ҡ��"
        });

        if(pointerp(obs=me->query_team()) )
        switch (random (4))
        {
                case 0:
message_vision("����������ƺ��ǰ�������������ӣ������ۻ����ң������ʧ��\n",me);
                        break;
                case 1:
message_vision("������󷨹����ƶ����������಻����˲�佫����Χ�����ġ�\n",me);
                        break;
                case 2:
message_vision("�������Խ��ԽС�����ν������˳�һ��������룬��������Ϣ֮�С�\n",me);
                        break;
                case 3:
message_vision("ֻ��������󰵺����а���֮�������˲������������ϵ������޷죬����֮������̾Ϊ��ֹ��\n",me);
                        break;
        }
        for(i=0;i<sizeof(obs);i++)
        {
                weapon=query_temp("weapon", obs[i]);
                power = obs[i]->query_skill("force",1)/10;
          addn_temp("apply/attack", power, obs[i]);
          addn_temp("apply/damage", power, obs[i]);
                switch (random(2))
                {
                        case 0:
message_vision("\n"+where[i]+"λ�ϵ�"+query("name", obs[i])+"������������񹦣���Ȼ����������������ǰһ��,����",me);
                                break;
                        case 1:
message_vision("\n"+where[i]+"λ�ϵ�"+query("name", obs[i])+"ͦ������������������ƮƮ��������硣ֻ��",me);
                                break;
//                       default:
                }
          err=catch(COMBAT_D->do_attack(obs[i],en,weapon,0));
          if (err)
          {
                  message("channel:debug","������󹥻����� err="+err,users());
                  return 1;
          }
                addn_temp("apply/attack", -power, obs[i]);
                addn_temp("apply/damage", -power, obs[i]);
                if( query("qi", en)*2 <= query("max_qi", en) )
                {
                        en->remove_all_enemy();
                        remove_call_out("do_end");
                        call_out("do_end", 1, me, en, 0);
                        return 1;
                }
        }
        j = random(sizeof(me->query_team()));
        enweapon=query_temp("weapon", en);
        if (enweapon)
          COMBAT_D->do_attack(en,obs[j], enweapon);
        else
          COMBAT_D->do_attack(en,obs[j], enweapon);
        if( query("qi", obs[j])*2 <= query("max_qi", obs[j]) )
        {
                message_vision(HIR+query("name", obs[j])+"һ��ſ�ڵ��ϣ�ˤ��������\n"NOR,me);
                en->remove_all_enemy();
                remove_call_out("do_end");
                call_out("do_end", 1, me, en, 1);
                return 1;
        }
        else if( query("qi", obs[j])*3 <= query("max_qi", obs[j])*2 )
        {
                message_vision(query("name", obs[j])+"������һ�������ˤ��������\n",me);
        }
        else if( query("qi", obs[j])*5 <= query("max_qi", obs[j])*4 )
                message_vision(query("name", obs[j])+"����û��˼��Σ�������վ���˲��ӡ�\n",me);

        remove_call_out("do_qixing");
        call_out("do_qixing", 1, me, en);
        return 1;
}
int do_end(object me, object en, int result)
{
        if( result == 1)
        {
                if( query_temp("pre_qixing", en) )
                {
                        set("qixing", 1, en);
                }
                delete_temp("pre_qixing", en);
                addn("combat_exp", 50000, en);
                addn("score", 30000, en);
                addn("potential", 10000, en);
                message_vision(HIR"\n�������"+query("name", en)+"�����ˡ�\n\n"NOR,me);
                message("channel:snow",HIR"��ͨ�桿"HIY+query("name", en)+"������������ˣ�\n"NOR,users());
        }
        else
        {
                delete_temp("pre_qixing", en);
                message("channel:snow",HIR"��ͨ�桿"HIY+query("name", en)+"û�ܴ����������\n"NOR,users());
    message_vision(HIR"\n$NЦ��Ц�����������Ϊȫ�����֮����\n"NOR,me);
                addn("score", -3000, en);
        }
        remove_call_out("do_back");
        call_out("do_back", 1, me);
        return 1;
}
int do_back(object me)
{
        object *obs, weapon;
        int i;

        if(pointerp(obs=me->query_team()) )
        {
                for(i=0;i<sizeof(obs);i++)
                {
                        if( objectp(weapon=query_temp("weapon", obs[i]) )
                                 && query("skill_type", weapon) == "sword" )
message_vision("$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ�����˳���������󡹡�\n", obs[i]);
                        else
message_vision("$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ�����˳���������󡹡�\n", obs[i]);

message_vision("$N���˸�鮵���ƶ���ȸ����ˣ�˵��Ϳ첽�뿪�ˡ�\n", obs[i]);
                        if( query("name", obs[i]) == "����" )
                                obs[i]->move("/d/quanzhen/shiweishi");
                        if( query("name", obs[i]) == "̷����" )
                                obs[i]->move("/d/quanzhen/rongwutang");
                        if( query("name", obs[i]) == "������" )
                                obs[i]->move("/d/quanzhen/jingxiushi");
                        if( query("name", obs[i]) == "�𴦻�" )
                                obs[i]->move("/d/quanzhen/laojundian");
                        if( query("name", obs[i]) == "����һ" )
                                obs[i]->move("/d/quanzhen/wanwutang");
                        if( query("name", obs[i]) == "�´�ͨ" )
                                obs[i]->move("/d/quanzhen/guangning");
                        if( query("name", obs[i]) == "�ﲻ��" )
                                obs[i]->move("/d/quanzhen/qingjing");
                }
        }///d/quanzhen/shiweishi
        me->dismiss_team();
}
