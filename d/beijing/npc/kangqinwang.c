#include <ansi.h>

inherit NPC;

void create()
{
        set_name("������", ({ "kang qinwang", "kang"}));
        set("title", HIY "��������" NOR);
        set("gender", "����" );
        set("age", 42);
        set("long", "\nֻ����һ����£�Ц�����棬��˭��������������������\n"+
                      "��������Ϊ��֮�������Ʋ��Թ�ɫ�����������ĵûʵ�\n���ġ�\n");
        set("shen_type", 1);
        set("combat_exp", 50000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge", 50);
        set_skill("unarmed", 50);

        setup();
        carry_object("/d/beijing/npc/obj/goldcloth2")->wear();
}

void init()
{
        object ob = this_player();

        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
        object man;

        if (! ob || environment(ob) != environment())
                return;

        if( query("meili", ob)<20 )
        {
                if (userp(ob))
                        message_vision("\n������һ��$N, ��ʱ��Ȼ��ŭ���е��������˰��������˸������£���\n", ob);

                if(! present("shi", environment(ob)))
                {
                        message_vision("��ʱ�����������������ӵ���$Nֱ�˹�����\n",ob);
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                }
                return ;
        }

        switch (random(5))
        {
                case 0:
                        message_vision("\n$N��һ����, ������������ӭ�˳�����Ц��������λ" +
                                       RANK_D->query_respect(ob) + "����������\n", ob);
                        if( query("meili", ob)<100 )
                        {
                                addn("meili", 10, ob);
                                message_vision(HIC "$N������ֵ����ˣ�\n" NOR, ob);
                                command("tell"+query("id", ob)+"�����ڵ�����ֵ��"+
                                        chinese_number(query("meili", ob))+"��");
                        }
                        break;
                default:
                        say("������Ц������֪��λ" + RANK_D->query_respect(ob) +
                            "�����ٺ����кι�ɣ�\n");
                        break;
        }
}

