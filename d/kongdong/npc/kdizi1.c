inherit NPC;
int ask_me(object me);


void create()
{
        set_name("��ἵ���", ({ "kongdong dizi","dizi" }) );
        set("gender", "����" );
        set("class","taoist");
        set("age",18);
	create_family("�����", 2, "����");
	set_wugong("shizi-zhan",100,100,1);
	set_wugong("jiben-qinggong",100,100,1);
	set_xiuwei("dodge",500);
	set_xiuwei("unarmed",500);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
        setup();
        carry_object(__DIR__"obj/cloth4")->wear();
}

void init()
{
        object ob;
        ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("greeting");
            call_out("greeting",1,ob);
            }
}

void greeting(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("��ἵ����������˸�Ҿ������λ"+RANK_D->query_respect(ob)
            +"���˵ص����վ���\n�ɵ�С��ѽ��\n");
        }
