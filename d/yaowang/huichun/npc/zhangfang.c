#include <ansi.h>
inherit NPC;

int ask_join();
int ask_box();

void create()
{
        set_name("������", ({ "guo laoliu", "guo", "laoliu", }));
        set("title", HIB"ҩ����"NOR+WHT"����"NOR);
        set("long", "���ǻش��õ��ʷ�����������ش��õ�������Ŀ��\n" );
        set("gender", "����");
        set("attitude", "friendly");

        set("age", 60);
        set("shen_type", 1);
        set("str", 17);
        set("int", 16);
        set("con", 18);
        set("dex", 20);
        set("max_qi", 150);
        set("max_jing", 150);
        set("jiali", 10);
        set("combat_exp", 5000);

        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);
        set_skill("yaogu-xinfa", 30);
        
        create_family("ҩ����", 3, "����");
        set("class", "bonze");

        set("inquiry", ([
                "ҩ����" : "Ҫ����ҩ���ȣ�����ask guo about ����",
                "join" : (: ask_join :),
                "����" : (: ask_join :),
                "��" : (: ask_join :),
                "��ĺ�" : (: ask_box :),
                "box" : (: ask_box :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        if( query_temp("work_pass", ob)){
                command("say ��������ҩ���ȵ��㣬�㻹����ȥ��\n");
                return 1; }
        if( query("party/party_name", ob) == "ҩ����" )
        {
                if( (int)ob->query_skill("medical",1)>=40) 
                {
                set_temp("work_pass", 1, ob);
                command("say ��λ�ֵ����ҽҩ�ھ����г�����������ҩ������Ҫ���˲ţ�\n");
                command("say �����Ը����Ե�ҩ����ȥ��ߵ��������һ��ѧϰ��\n");
                return 1;
                }
                
        }
        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}


int ask_join()
{
        mapping party; 
        object me;
        me=this_player();

        if( query("family/family_name", me) == "ҩ����" )
                {
                command("say "+RANK_D->query_respect(me)+
                        "���Ѿ���ҩ���ȵ����ˣ���Ҫ����ʲô��\n");
                return 1; 
                }

        if( query("family/family_name", me) )
                {
                command("say "+RANK_D->query_respect(me)+
                        "���Ѿ�����ʦָ�㣬���ǻ�ȥ�úð�Ч��ʦ�Űɣ�\n");
                return 1; 
                }

        command("ok"+query("id", me));
        command("say �����ڻش������°ɣ�ʱ����������Ϳ��Խ���ҩ�����ˣ�\n");
        command("recruit"+query("id", me));
        if( query("class", me) != "bonze" )
                set("class", "bonze", me);
        set("title", "�ش������õ���", me);
        command("say "+RANK_D->query_respect(me)+
                "���Ҫ���Ŭ���ɻ��\n");
        return 1;
}

int ask_box()
{
        object ob, me;
        me=this_player();

        if( query("family/family_name", me) != "ҩ����"){
                command("say "+RANK_D->query_respect(me)+
                        "�㲻��ҩ���ȵĵ��ӣ���ĺв��������㣡\n");
                return 1; }

        if( present("zhenjiu he", me) ) {
                command("say "+RANK_D->query_respect(me)+
                        "���������ϲ�������Ҫ��ô���ʲô�أ�\n");
                return 1; }

        if( (int)me->query_skill("medical",1)<40 ) {
                command("say "+RANK_D->query_respect(me)+
                        "�����ڻ�����ʹ����ĺУ�\n");
                return 1; }

        ob = new(__DIR__"obj/zhenjiu");
        ob->move(me);

        message_vision(YEL"��������$Nһ��"+query("name", ob)+"��\n"NOR,me);

        command("say "+RANK_D->query_respect(me)+
                "���Ҫ���Ŭ������\n");
        return 1;
}
