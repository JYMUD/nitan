// zhixiang.c �������

//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

//string ask_job();
//void greeting(object);
//int do_say(string);
//int do_kill(string);

void create()
{
        set_name("�������", ({ "lingxu daozhang", "lingxu", "daozhang" }));
        set("long","�������䵱���������������ͤ�ĵ��ӡ�ÿ�����䵱�������̫���ˣ�����\n�����µļ�����ľ��ʿ��æ�������ˡ�\n");
        set("gender", "����");
        set("nickname", "�������");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 800);
        set("max_jing", 400);
        set("neili", 700);
        set("max_neili", 700);
        set("jiali", 30);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 70);
        set_skill("taiji-shengong", 60);
        set_skill("dodge", 70);
        set_skill("tiyunzong", 70);
        set_skill("unarmed", 70);
        set_skill("taiji-quan", 70);
        set_skill("parry", 70);
        set_skill("sword", 70);
        set_skill("wudang-jian", 60);
        set_skill("wudang-quan", 60);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");

        /*
        set("inquiry", ([
                "���" : "������Ʋ��ף�����������ˣ��Ϸ����߷��ܵ�֮��\n",
                "����" : "���㣿ͯ���޼ɣ�ͯ���޼ɣ�Ҫ˵������ǣ�\n",
                "����" : "���õ���������Ӳ��ϣ�����Ϊ���䵱���Ӻ�ɽ����ͼ�ʱ���\n",
                "�Ϸ���" : "�Ϸ��׾���������������Ǯ�������幤��\n",
                "����" : "�������������������Ǯ�������幤��\n",
                "����" : "�䵱������ɽ�Ÿ�����\n",
                "����" : "�䵱���־������湬��\n",
                "����" : "���Ͼ��Ǻ��ɺ���أ���ÿ�춼Ҫ����ȥ������\n",
                "����" : (: ask_job :),
                "��ľ" : (: ask_job :),
                "job"  : (: ask_job :),
                "wook" : (: ask_job :),
                "����" : "������ÿ�춼��Ҫ��ȥ�������������������Щ�������Ǹ��á�\n",
                "�ɻ�" : "������ÿ�춼��Ҫ��ȥ�������������������Щ�������Ǹ��á�\n",
        ]));
        set("chat_chance", 5);
        set("chat_msg", ({
                "�������˵����������Ʋ��ף�����������ˣ��Ϸ����߷��ܵ�֮��\n",
                "�������˵�������ɺ���ض����������ĺò��ϡ�\n",
                "�������˵������������Ǵ������￳��������\n",
                "�������˵�����䵱�����ֺͰ��ֶ����˼������ˣ���û������ͨ����\n",
                "�������˵����������ʱ��Ҫ���С�ģ����ɳ������ĵ�ʿ����Щ����ȥ�޻ء�\n",
        }) );

        set("wanted", ({ HIR"��������"NOR, HIG"�������"NOR }));
        */
        create_family("�䵱��", 4, "����");

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}
/*
void init()
{
        object me = this_player();

        ::init();
        if( interactive(me) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object me)
{
        mapping myfam;
        object where, ob;

        ob = this_object();
        myfam=query("family", me);
        where = environment(ob);

        if( !me || !living(ob) ||
                strsrch(file_name(where), "/d/wudang/") < 0 ||
                environment(me) != environment() )
                return;
        if( query("wdjob/supervisor", me) == "�������" )
        {
                me->set_temp("apply/short",
                        (query("id", {HIW"�䵱��ľ��"NOR+query("name", me)+"("+capitalize(me))+")"}));
                message_vision("���������ס$N��������ȥ�ҵ�"+query("wdjob/object", me)+"���������ˣ�\n",me);
        }
        else
                if ( myfam && myfam["family_name"] == "�䵱��" )
                {
                        if( query("wudang/offerring", me)<query("age", me) )
                                message_vision("�����������$Nŭ����������ھ���뱻���ɽ�Ų�Զ�ˣ�\n", me);
                        else if( query("wudang/offerring", me)<
                                        query("age", me)*4/3 )
                                message_vision("�����������$N�����ĳ��������䵱���ӣ���Ӧ������ף�"+RANK_D->query_respect(me)+ "Ҫ��ǿŬ������\n",me);
                        else if( query("wudang/offerring", me)<
                                        query("age", me)*2 )
                                message_vision("���������$N˵����" + RANK_D->query_respect(me) + "�ܾ�ְ����ڵ�����������⡣\n", me);
                        else message_vision("�������ָ��$N��̾����" + RANK_D->query_respect(me) + "���ھ�������ұ���ģҲ��\n", me);
                }
                else if( query("title", me) == "�䵱��ͯ" )
                        message_vision("�����������$N˵��������Ŭ������ȡ��������ɽ�š�\n", me);
                else if( query("wudang/offerring", me)>query("age", me)*2 )
                        message_vision("�����������$N�ʺ����ԭ���Ǵ���͵��ˣ�ʧӭ��ʧӭ��\n", me);
                else if( query("wudang/offerring", me)>query("age", me) )
                        message_vision("�����������$N�ʺ������λ������ˣ�\n", me);
                else
                {
                        set("wudang/yuzhen_block", 1, me);
                        say("�������˵�����粻�Ǿ��㣬������ɽ��\n");
                }
}

string ask_job()
{
        object ob;
        string what;
        string *wanted;

        ob = this_player();

        if( query("wdjob/supervisor", ob) )
        {
                command("say ���һ�ݻ����û����������ڶ��ݣ�");
                if( query("wdjob/supervisor", ob) == "�������" )
                {
                        add_action("do_say", "say");
                        return("�����ɲ������ɸ���Ļ����ֱ�Ӹ���˵��ɲ��ˡ�");
                }
                return ("�����ɲ��ˣ�����ֱ��ȥ����"+query("wdjob/supervisor", ob));
        }
        if (query_temp("stock") > 10)
                return ("�������ˣ�����Ļ���Ҷ��������ˡ�");
        add_temp("stock", 1);
        wanted = query("wanted");
        what = wanted[random(sizeof(wanted))];

        set("wdjob/supervisor", "�������", ob);
        set("wdjob/object", what, ob);
        set("wdjob/description", what, ob);
        set("wdjob/wage", 3, ob);
        set_temp(query("id", "apply/short", ({HIW"�䵱��ľ��"NOR+query("name", ob)+"("+capitalize(ob))+")"}), ob);
        message_vision("����������˶�$N˵�����������ã�������ȱ���֣�\n", ob);
        return ("����Ҫ"+ what +CYN"�����ã���ȥ���ҿ�Щ���ɣ�\n");
}

int accept_kill(object obj)
{
        object ob=this_object();
        if (obj->is_killing(this_object()) ) return 1;
        if( query("wdjob/supervisor", obj) == "�������" )
        {
                message_vision("$N��ɱ��$n��\n$n������$N���������췴�ģ������������\n", obj, ob);
                set("wdjob/wage", 0, obj);
                return 0;
        }
        else if( query("family/family_name", obj) == "�䵱��" )
        {
                message_vision("$N��ɱ��$n��\n$n������$N�������ұ�ͬ�ţ�ȴΪ�����຦���ң�\n$n��$N�ܲ����⣡\n", obj, ob);
                addn("wudang/offerring", -20, obj);
                return 0;
        }
        else
        {
                command("family ��λ�䵱ͬ�ţ�" + obj->name() + "���" + RANK_D->query_rude(obj) + "�������䵱��Ұ������һ������ϣ�");
          return 1;
        }
}

int accept_object(object who, object ob)
{

        object obn, wage;
        int i, j, k;
        string *wanted;


        if( query("money_id", ob) && ob->value() >= 100*query("age", who) )
        {
                if( (query("family/family_name", who)) == "�䵱��" )
                        tell_object(who,"�����������һЦ����Ȼ��"+((query("gender", who) == "Ů��")?"��":"��")+"��˳���������������������һ֦������ȥ����ɡ�\n");
                else
                        tell_object(who, "�����������һЦ����Ȼʩ����˳���������������������һ֦����ʩ����ȥ����ɡ�\n");
                obn = new("/d/wudang/obj/incense");
                obn->move(who);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        if( (query("family/family_name", who)) == "�䵱��" )
                                tell_object(who,"�������������̾�����䵱ɽ���ʢ��ȫ�����"+((query("gender", who) == "Ů��")?"��":"��")+"������������𰡣�\n");
                        else
                                tell_object(who, "�������������̾�����䵱ɽ���ʢ��ȫ����������������Ͱ���\n");

                        return 1;
                }
                else if( (query("wdjob/supervisor", who) == "�������") && 
                                query("wdjob/object", who) == 
                                query("name", ob) )
                {
                        i=query("wdjob/wage", who);
                        if (i < 0 || i >= 13) i = 2;

                        wage = new("/clone/money/silver");
                        wage->set_amount(i);
                        wage->move(who);

                        command("say ������λ"+RANK_D->query_respect(who)+"�ˡ�");
                        command("thumb"+query("id", who));
                        message_vision("���������$N"+chinese_number(i)+"��������Ϊ�������ꡣ\n", who);

                        addn("combat_exp", 1+random(i), who);
                        addn("wudang/offerring", 1+random(i/4), who);
                        delete_temp("apply/short", who);
                        addn("wdjob/succeed", 1, who);
                        delete("wdjob/supervisor", who);
                        delete("wdjob/description", who);
                        delete("wdjob/wage", who);
                        delete("wdjob/object", who);

                        return 1;
                }
                else if( member_array(query("name", ob),(string*)query("wanted")) != -1 )
                {
                        if ( query_temp("stock") > 10 )
                        {
                                say("�������ҡҡͷ˵����л��λ" +RANK_D->query_respect(who)+"��������Ҫ�Ĳ��϶��Ѿ��������ˡ�\n");
                                return 1;
                        }
                        message_vision("����������˶�$N˵�����������ã�������������Ҫ�ģ�\n", who);
                        add_temp("stock", 1);
                        addn("wudang/offerring", random(1), who);
                        i=query("wdjob/wage", who);
                        j=query("wudang/offerring", who)-query("age", who)*2;
                        if( (query("family/family_name", who) == "�䵱��") && 
                                (j > 0 ) )
                        {
                                addn("combat_exp", (j+i)/2+random(i+j), who);
                                k = j/2 + random(i);
                                addn("potential", k, who);
                                if ( random(2) )
                                {
                                        tell_object(who, "�������������һ֦������ȥ����ɡ�\n");
                                        addn("wudang/offerring", -1-random(3), who);
                                        obn = new("/d/wudang/obj/incense");
                                        obn->move(who);
                                }

                        }
                        else if( query("family/family_name", who) == "�䵱��" )
                        {
                                addn("combat_exp", i/2+random(i), who);
                                k = 1+random(i);
                                addn("potential", k, who);
                        }
                        else addn("combat_exp", 1+random(i), who);
                        command("say �������ԸΪ�䵱Ч�����պ�س��䵱������");
                        command("thumb"+query("id", who));
                        return 1;
                }
        return 0;
}


int do_say(string arg)
{
        object ob, who;

        who = this_player();
        ob = this_object();

        if ( (string)arg != "�ɲ���") return 0;
        if( query("wdjob/supervisor", who) != query("name", ob))return 0;

        message_vision("$N����˵�����������ɵĻ��Ҹɲ��ˡ�\n", who);
        command("pat"+query("id", who));
        command("say û��ϵ���´κúøɣ�");

        addn_temp("stock", -1, this_object());
        delete_temp("apply/short", who);
        addn("wdjob/fail", 1, who);
        delete("wdjob/supervisor", who);
        delete("wdjob/description", who);
        delete("wdjob/wage", who);
        delete("wdjob/object", who);

        return 1;
}
*/
