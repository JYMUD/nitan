inherit NPC;


void create()
{
        set_name("�ջ�С��ʿ", ({ "shaohuo daoshi","daoshi" }) );
        set("title","��ἵ���");
        set("gender", "����" );
        set("class","taoist");
        set("age",16);
	create_family("�����", 2, "����");
	set_wugong("dahong-quan",20,20,1);
	set_xiuwei("unarmed",100);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("apply_food",15);
        setup();
        carry_object(__DIR__"obj/cloth3")->wear();
}

/*void init()
{
        object ob;
       ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("greeting");
            call_out("show_msg",1,ob);
            }
        add_action("do_yao","yao");
}

void show_msg(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("�⼸��С��ʿ����æ���ҵ�����������û��ע�⵽�㡣\n");
}

int do_yao(string arg)
{
        object ob;
        ob = this_player();
        if(!arg || (arg!="food" && arg!="ʳ��") )
        {
                tell_object(ob,"С��ʿת����������Ҫʲô��\n");
                return 1;
        }

        if(ob->query("family/family_name")!="�����")
        {
               message_vision("С��ʿ����$Nҡ��ҡͷ˵����λʩ����ʵ�ڶԲ���\n"
                        "ի����û�����ã�������һ�����\n");  
               return 1;
        }
        printf("С��ʿæ˵����λ%s������û�ã������Ҹ���㶫���伢�ɡ�\n",
                (ob->query("gender")=="����") ? "ʦ��" : "ʦ��" );
        message_vision("С��ʿ��ʳ���﷭��һ���ر���һ����«��\n",ob);
        message_vision("С��ʿ��$Nһ���ر���\n",ob);
        message_vision("С��ʿ��$Nһ����«��\n",ob); 
        new(__DIR__"obj/subing")->move(ob);
        new(__DIR__"obj/hulu")->move(ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if(ob->value() >= 1000)
        {
                message_vision("С��ʿ���ɵؽӹ�"+ob->name()+"����������ţ�\n"
                "����ô����˼�أ�\n",who);
                message_vision("С��ʿ�����룬��ʳ�����ø�&Nһ���ر���һ����"
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
*/
                
