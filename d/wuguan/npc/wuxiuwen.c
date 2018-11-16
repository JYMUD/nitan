#include <ansi.h>
inherit NPC;

string give_tools();

void create()
{
        set_name("������", ({"wu xiuwen", "wu", "xiuwen"}));
        set("title", HIY "����������" NOR);
        set("gender", "����");
        set("age", 21);
        set("long", "���ǹ����Ķ����ӣ�����ǿ�ɣ�ר�Ÿ�����ڡ�\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 24);
        set("str", 20);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 50);
        set("combat_exp", 400000);
        set("score", 20000);
         
        set_skill("force", 160);
        set_skill("yijin-duangu", 160);
        set_skill("dodge", 160);
        set_skill("shexing-lifan", 160);
        set_skill("finger", 160);
        set_skill("sun-finger", 160);
        set_skill("sword", 160);
        set_skill("yuenv-jian", 160);
        set_skill("parry", 160);
        set_skill("literate", 140);
        set_skill("jingluo-xue", 160);
        set_skill("martial-cognize", 140);

        map_skill("force", "yijin-duangu");
        map_skill("dodge", "shexing-lifan");
        map_skill("finger", "sun-finger");
        map_skill("sword", "yuenv-jian");
        map_skill("parry", "jinyuan-gun");

        prepare_skill("finger", "sun-finger");

        create_family("����", 2, "����");

        set("inquiry", ([
                "����" : "������ʦĸ��",
                "����" : "������ʦ����",
                "����" : (: give_tools :),
                "tools" : (: give_tools :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "dodge.gui" :),
                (: perform_action, "powerup" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
	{
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
	
string give_tools()
{
       	object tools, ob, me;

       	me = this_object();
       	ob = this_player();

       	if( query_temp("mark/����", ob) )
		return "�Ҳ����Ѿ�����������ô��ô���£�";

       	if( query_temp("mark/����", ob) )
		return "�㻹���ȵ�Ү��ʦ���Ǹ�������˵�ɡ�";

       	if( !((query_temp("job_name", ob) == "��ľͷ" )
	 || (query_temp("job_name", ob) == "����" )
            || (query_temp("job_name", ob) == "���˵�" )
	 || (query_temp("job_name", ob) == "����" )
	 || (query_temp("job_name", ob) == "��ɨ��")) )
             	return "����û���칤��������Ҫʲô���ߣ�";

       	if( query_temp("job_name", ob) == "����" )
		tools = new("/d/wuguan/obj/chutou");
       	else
	if( query_temp("job_name", ob) == "���˵�" )
		tools = new("/d/wuguan/obj/piao");
        else
	if( query_temp("job_name", ob) == "��ľͷ" )
		tools = new("/d/wuguan/obj/juzi");
        else
	if( query_temp("job_name", ob) == "����" )
		tools = new("/d/wuguan/obj/chaidao");
        else
		tools = new("/d/wuguan/obj/saozhou");

        tools->move(this_player());

        message_vision(HIC "$N" HIC "����$n" HIC "һ�ѹ��ߡ�\n"
                       NOR, me, ob);
        set_temp("mark/����", 1, ob);
        return "�����������ˣ���ҪС�ı��ܣ���Ū���ˡ�";
}

int accept_object(object me, object obj)
{
      	object ob;
      	me = this_object();
      	ob = this_player();

      	if( !(query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/ɨ����", ob)) )
	{
              	command("say �㻹û��ɹ�������ô�ͻ����������ˣ�͵����");
	      	return 0;
        }

        if( (query("id", obj) != "ju zi" )
	 && (query("id", obj) != "chu tou" )
	 && (query("id", obj) != "shui piao" )
	 && (query("id", obj) != "sao zhou" )
	 && (query("id", obj) != "chai dao") )
	{
              	command("say �㻹�����˰ɣ��Ҵ�û�з����������ߡ�");
              	return 0;
        }

	if( !query_temp("job_name", ob) )
	{  
              	command("shake");
              	command("say ��û�з���������������ǲ��ǻ����ˣ�");
              	return 0;
        }
     	command("nod");
     	command("say �ɵò���������ȥҮ��ʦ���Ƕ���ȡ���Ͱɡ�");
        set_temp("mark/����", 1, 	ob);
        destruct(obj);
     	return 1;
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

        if( query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/������", ob )
	 || query_temp("mark/ɨ����", ob) )
	{
		command("nod "+query("id", ob));
         	command("say ��Ĺ��������ˣ������ڰѹ��߻����Ұɡ�");
         	return; 
        }

        if( query_temp("mark/����", ob) )
		return 0; 

        if( (query_temp("job_name", ob) == "��ľͷ" )
	 || (query_temp("job_name", ob) == "����" )
	 || (query_temp("job_name", ob) == "���˵�" )
	 || (query_temp("job_name", ob) == "����" )
	 || (query_temp("job_name", ob) == "��ɨ��") )
	{
       		command("nod "+query("id", ob));
       		command("say �������������칤��(" HIY "ask wu xiuwen about ����"
                        NOR + CYN ")�İɡ�" NOR);
       	}
}
