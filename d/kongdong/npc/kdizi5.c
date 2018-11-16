inherit NPC;


void create()
{
        set_name("�ջ�С��ʿ", ({ "shaohuo daoshi","daoshi" }) );
        set("title","��ἵ���");
        set("gender", "����" );
        set("class","taoist");
        set("age",16);
	create_family("�����", 2, "����");
	set_wugong("dahong-quan",60,60,1);
	set_wugong("jiben-qinggong",60,60,1);
	set_xiuwei("unarmed",250);
	set_xiuwei("dodge",100);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("food_apply",15);
        setup();
        carry_object(__DIR__"obj/cloth3")->wear();
}

void init()
{
        object ob;
        if(interactive(ob=this_player()) && !is_fighting()){
		remove_call_out("show_msg");
            call_out("show_msg",1,ob);
            }
        add_action("do_yao","yao");
}

void show_msg(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("�⼸��С��ʿ����æ���ҵ�����������û��ע�⵽�㡣\n");
}
int do_yao()
{
    object who = this_player();
    object me = this_object();

    if( who->query("family/family_name")!="�����" || query("food_apply") < 0 )
        {
               message_vision("С��ʿ����$Nҡ��ҡͷ˵����λʩ����ʵ�ڶԲ���\n"
                        "ի����û�����ã�������һ�����\n",who);  
               return 1;
        }
    if ( (who->query("water") >= who->max_water_capacity()/2)
        &&(who->query("food") >= who->max_food_capacity()/2) ){
        return notify_fail("��Եñ����ģ��ȵ�������������ʲô�ң���\n");
        }

    message_vision("$N���Ŷ��ӿ�������ö�$n˵��\n"
        "��Сʦ�֣�����ʣ����ʵ���Ƕ��ò����ˡ���\n\n",who,me);
        printf("С��ʿæ˵����λ%s������û�ã������Ҹ���㶫���伢�ɡ�\n",
                (who->query("gender")=="����") ? "ʦ��" : "ʦ��" );
    who->set("food" ,who->max_food_capacity());
    who->set("water",who->max_water_capacity());

    return 1;
}

int accept_object(object who, object ob)
{
        if(ob->value() >= 1000)
        {
                message_vision("С��ʿ���ɵؿ���"+ob->name()+"����������ţ�\n"
                "����ô����˼�أ�\n",who);
                message_vision("С��ʿ�����룬��ʳ�����ø�$Nһ���ر���һ����"
                        "«��\n˵��Ҫ����������ɱ�˵�����ø���ġ�\n",who);
                message_vision("С��ʿת����ȥ����������\n",who);
                new(__DIR__"obj/subing")->move(who);
                new(__DIR__"obj/hulu")->move(who);
                return 1;
        }
        else 
        {
                message_vision("С��ʿҡҡͷ��ʦ��˵�����������Ҫ���˵Ķ�����\n",who);
                return 0;
        }
}

                
