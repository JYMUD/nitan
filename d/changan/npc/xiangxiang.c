//xiangxiang.c

inherit NPC;

int execute_ask();

void create()
{
        set_name("����", ({ "xiangxiang", "xiang" }));
        set("title","��Ա��֮Ů");
        set("gender", "Ů��");
          set("age", 17);
          set("attitude", "peaceful");
          set("shen_type", 1);
          set("per", 40);
          set("int", 40);
          set("max_kee", 600);
          set("max_gin", 600);
          set("max_sen", 600);
          set("force", 700);
          set("max_force", 700);
          set("force_factor", 50);
          set("max_mana", 700);
          set("mana", 700);
          set("mana_factor", 40);
          set("combat_exp", 250000);
          set_skill("unarmed", 60);
          set_skill("dodge", 60);
          set_skill("parry", 60);
          set_skill("force", 60);
        set("chat_chance", 15);
        set("chat_msg", ({
                "�����뵽���Ĵ����̲�ס������ޡ�\n",
                "����������˼�ĵ���˭�ܸ��ҵ��Ӹ��Ž��������ҡ�\n",
        }) );
        set("inquiry", ([
                "��" : (: execute_ask() :),
                "����" : (: execute_ask() :),
                "letter" : (: execute_ask() :),
                "��" : (: execute_ask() :),
        ]));

        setup();
           carry_object("/d/changan/npc/obj/skirt")->wear();
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment())
                return;
        command("look "+query("id", me));
        return ;
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        call_out ("check_rescure",1,this_player());
}

int execute_ask()
{
          object who = this_player();
          object me = this_object();
          object letter = 0;

        if( query("combat_exp", who)<30000 )
        {
                    command ("shake");
                    return 1;
        }
        if (present("da shou",environment(me)))
        {
                    command ("fear");
                    return 1;
        }
        if (present("huang yi",environment(me)))
        {
                    command ("shake");
                    return 1;
        }
        if( query("given", me) )
        {
                    command ("shake");
                    return 1;
        }
          command ("nod");
          set("given", 1, me);
          letter = new ("/d/changan/npc/obj/letter");
          letter->move(me);
          command("whisper "+query("id", who)+
                " ������Ž����ҵ��������������ң�");
          command("give "+query("id", who)+" "+query("id", letter));
          who->save();
          return 1;
}

int check_rescure(object who)
{
          object me = this_object();
          object yupei;

          if (present("da shou",environment(me)))
                    return 1;
        if (present("huang yi",environment(me)))
                    return 1;
        if (! who) return 1;
        yupei = present("yu pei",who);

          if (! yupei)
                    return 1;
          if( query("leader", me) )
                    return 1;
          set("leader",query("id",  who), me);
          message_vision("$N��$n���е�˵�������ˣ���������ȥ���ҵ���\n",me,who);
          command("follow "+query("id", who));
          set_temp("no_return ", 1, me);
          return 1;
}

void unconcious()
{
          ::unconcious();
          die();
}
