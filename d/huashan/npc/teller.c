// teller.c

inherit KNOWER;

int do_forge();

void create()
{
        set_name("������", ({ "fortune teller", "teller" }) );
        set("gender", "����" );
        set("age", 48);
        set("long", "�������Ǹ������ԵĽ�����ʿ�������д���š�������\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", -1);

        set_skill("unarmed", 30);
        set_skill("dodge", 25);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set("combat_exp", 2500);

        set("attitude", "peaceful");
        set("inquiry", ([
                "д��" : "������˵��������д�ţ�ÿҳ��ʮ�ġ�\n",
                "д����" : "������˵���������ø����ּ�д������ÿ������������\n",
                "α��" : (: do_forge :),
        ]) );

        setup();
        add_money("silver", 5);
}

int do_forge()
{
        say("��������ֻ�۾�����ɨ��ɨ�����ٺٺ١��ĸ�Ц�˼���...\n");
        write("��������������˵���������Ҵ�ţ����֤��ĸ�ԭ��"
              "����һģһ����ÿ����\n"
              "                           ��ʮ�������������ۡ�\n");
        set_temp("marks/��", 1, this_player());
        return 1;
}

int accept_object(object who, object ob)
{
        object letter;

        letter = new(__DIR__"obj/letter");

        if( query("id", ob) == "letterpaper" )
        {
                if( query_temp("marks/��", who) )
                {
                        set_temp("marks/��3", 1, this_player());
                        write("���������˵������������ף�������ʮ����������\n");
                        set_temp("marks/��", 0, this_player());
                        call_out("destroy", 1, ob);
                        return 1;
                }else if( query_temp("marks/��2", who) )
                {
                        write("������ƤЦ�ⲻЦ�Ķ���˵����α����"
                              "���ſ��ǹ�ϵ�ش󰡣��ö�����ʮ����\n");
                        set_temp("marks/��4", 1, this_player());
                        set_temp("marks/��2", 0, this_player());
                        call_out("destroy", 1, ob);
                        return 1;
                }
                return 0;
        }
       
        if (ob->value() >= 5000)
        {
                if( query_temp("marks/��4", who) )
                {
                        write("���������˵���������������ˣ���" +
                              RANK_D->query_respect(who) + 
                              "Ҫ�ǳ����£�ǧ������˵����ѽ��\n");
                        say("���������"+query("name", who)+"һ�����š�\n");
                        set_temp("marks/��4", 0, this_player());
                        letter->move(who);
                        return 1;
                }

                if( query_temp("marks/��3", who) )
                {
                        write("������ƤЦ�ⲻЦ�Ķ���˵����α�������"
                              "���ǹ�ϵ�ش󰡣��ö�����ʮ����\n");
                        set_temp("marks/��4", 1, this_player());
                        set_temp("marks/��3", 0, this_player());
                        return 1;
                }

                if( query_temp("marks/��", who) )
                {
                        write("���������˵��������α��ʲô��? ��"
                              "���ø��������ɡ�\n");
                        set_temp("marks/��2", 1, this_player());
                        set_temp("marks/��", 0, this_player());
                        return 1;
                }
                say("������һ�漱æ��Ǯ��������һ��Ц����˵����" +
                    RANK_D->query_respect(ob) + "������ô�ҵ���\n");
                return 1;
        }

        if (ob->value() >= 500)
        {
                say("������Ц����˵��������д���ˣ���"
                    "���������ɣ���л���ա�\n");
                return 1;
        }

        if (ob->value() >= 50)
        {
                say("������Ц����˵������д���ˣ����պ��ˣ���л���ա�\n");
                return 1;
        }
        return 0;
}

void destroy (object ob)
{
        destruct(ob);
        return;
}
