inherit NPC;
#include <ansi.h>

void create()
{
        set_name("��԰����", ({ "caiyuan guanshi", "guanshi" }) );
        set("gender", "����" );
        set("age", 50);
        set("long", "���ǲ�԰���£�ר�ܲ�԰���С���£�\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("inquiry", ([
             	"����" : "�����������ʵʵ���ҳ����Ӳݣ�û���ҵ����⣬������ȥ������",
        ]) );
        setup();
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

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        if( query_temp("job_name", ob) != "����")return ;

        if (! (present("chu tou", ob)))
        {
        	command("hmm"+query("id", ob));
        	command("say �㻹û�칤�߰ɣ�ȥ����Ʒ������үҪ��������\n");
        	return;
        }

        if( !(query_temp("job_name", ob) != "����") )
        {
        	command("nod"+query("id", ob));
                command("say ��Ү�ɴ�ү�Ը������İɣ�������������(" HIY
                        "chu cao" NOR + CYN ")���ˡ�\n" NOR);
        }
}