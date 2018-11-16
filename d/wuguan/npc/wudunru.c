#include <ansi.h>
inherit KNOWER;

inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("�����", ({ "wu dunru", "wu", "dunru" }));
        set("title", HIY "���������" NOR);
        set("gender", "����");
        set("age", 23);
        set("long", "���ǹ�������ӣ���ò�Ͱ���һ�쵽��Ц�Ǻǵġ�\n");
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
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/wuguan/guofu_dating",
                   "id"        : "guo jing", ]),
        }));

        set("guarder", ([
                "refuse_carry": CYN "$N" CYN "��$n" CYN "�ȵ����㱳��"
                                "������ʲô�ˣ��������ҷ�������\n" NOR,
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
        if (clonep()) keep_heart_beat();
        carry_object("/clone/misc/cloth")->wear();
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom"))
           && find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character()
                           || interactive(ob)
                           || playerp(ob)
                            || query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob) )
                           && find_object(start_room) == environment())
                                continue;

                        if( query("id", ob) == "guojing"
                           || base_name(ob) == CORPSE_OB)
                                continue;

                        message_vision(CYN "$N" CYN "�������ܣ�ҡ��ҡͷ��ת��"
                                       "������ȥ��\n" NOR, ob);
                        ob->move("/d/xiangyang/westjie1");
                }
        }
        ::heart_beat();
}

void init()
{
        object ob;
        int exp, pot, sc;

        ::init();

        exp = 3000 + random(500);
        pot = 1000 + random(100);
        sc = 50 + random(30);

        if (interactive(ob = this_player())
           && ! is_fighting())
	{
        	if (! ob || environment(ob) != environment())
			return;

        	if( query("combat_exp", ob)<5000
           	 && !query("mark/guofu_ok", ob )
           	 && !query("mark/guofu_over", ob )
           	 && !query("mark/guofu_out", ob) )
		{
        		command("say ��λ" + RANK_D->query_respect(ob) +
                        	"���书��ô���ô�������أ�\n");
        		command("whisper"+query("id", ob)+"������"
                        	"ֵ�������ң�����������\n���˵�Χ������"
                        	"���Ǳ����߶��ĺá����ǹ�������ȱ������"
                        	"��\n�ӣ���������Ȥ���ǿ��Խ��� (" HIY
                        	"join ����" NOR + WHT ")���æ��˳��ѧ"
                        	"��\n�������������֪" + RANK_D->query_respect(ob) +
                        	"������Σ�\n");
		} else
        	if( query("combat_exp", ob) >= 20000
           	 && query("mark/guofu_ok", ob) )
		{
        		command("look"+query("id", ob));
        		command("haha");
        		command("whisper"+query("id", ob)+"����"
                                "�����벻����Ľ�չ��\n�����٣�������"
                                "�������޶���ô�������Ƕ�ȥ���������ɡ�\n");

delete("mark/guofu_ok", 			ob);
set("mark/guofu_out", 1, 			ob);

addn("combat_exp", exp, 	ob);
        addn("potential", pot, 	ob);
                addn("score", sc, 	ob);
                        tell_object(ob, HIC "ͨ���ڹ����ڵĶ���������"
                                        "��" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) +
                                        "��Ǳ��\n�Լ�" + chinese_number(sc)
                                        + "�㽭���������似�õ���������"
                                        "\n\n" NOR);
		} else
        	if( query("mark/guofu_over", ob) )
		{
        		command("sneer"+query("id", ob));
		} else
        	if( query("mark/guofu_out", ob) )
		{
        		command("nod"+query("id", ob));
		} else
        	if( query("combat_exp", ob)>20000
           	 && !query("mark/guofu_ok", ob )
           	 && !query("mark/guofu_over", ob )
           	 && !query("mark/guofu_out", ob) )
		{
        		command("hi"+query("id", ob));
        		command("say ��������ֵ����ʱ�ڣ������к�������ˡ�");
		} else
        	if( query("combat_exp", ob)<20000
           	 && query("mark/guofu_ok", ob) )
		{
        		command("look"+query("id", ob));
        		command("hmm");
        		command("say �Ͽ�ɻ�ȥ��û��Ϲ���ʲô��");
		}
        }
        add_action("do_join", "join");
        add_action("do_kill", "hit");
        add_action("do_kill", "kill");
        add_action("do_kill", "touxi");
        add_action("do_kill", "fight");
        add_action("do_yun", "yun");
        add_action("do_yun", "exert");
}

int do_yun(string arg)
{
        object ob = this_object();

        if (arg == "roar")
        {
                message_vision(CYN "\n�����ȵ���ʲô�ˣ�������"
                               "ǰ���ɲ��������ţ�\n" NOR, ob);
                return 1;
        }
        return 0;
}

int do_kill(string arg)
{
        object ob = this_object();

        if (arg != "wu dunru"
           && arg != "wu"
           && arg != "dunru" )
        {
                message_vision(CYN "\n�����ȵ���ʲô�ˣ�������"
                               "ǰ���ɲ����������\n" NOR, ob);
                return 1;
        }
        return 0;
}

int do_join(string arg)
{
        object ob = this_player();

        if (! arg
           && arg != "guofu"
           && arg != "����")
                return notify_fail(CYN "�����üͷһ�壬�����㵽"
                                   "��Ҫ��ʲô����ô˵����������"
                                   "�ģ�\n" NOR);

	if( query("mark/guofu_over", ob) )
                return notify_fail(CYN "�������Ц����ʦ��������"
                                   "�����㻹����������\n" NOR);

	if( query("mark/guofu_ok", ob) )
                return notify_fail(CYN "�������ü�����㲻���Ѿ�"
                                   "�������𣿸Ͽ�ɻ�ȥ������ʲ"
                                   "ô��\n" NOR);

	if( query("mark/guofu_out", ob) )
                return notify_fail(CYN "�����΢Ц���������ڵ���"
                                   "���Ѿ���һ���ĵ����ˣ����Ƕ�"
                                   "���������ɡ�\n" NOR);

        if( query("combat_exp", ob)>5000 )
                return notify_fail(CYN "�����΢Ц��������������"
                                   "��̫ί�����ˣ��㻹����ı��·"
                                   "�ɡ�\n" NOR);

	if( query_temp("mark/guofu_join", ob) )
	{
        	message_vision(HIC "\n$N" HIC "��$n" HIC "���˵�"
                               "ͷ��˵�������ã����á����˹���һ"
                               "�о�Ҫ\n����ذ��£�������ȥҮ��"
                               "�������������㰲������ġ�\n"
                               "\n", this_object(), ob);
set("mark/guofu_ok", 1, 		ob);
                set("startroom", "/d/wuguan/guofu_dayuan", ob);
delete_temp("mark/guofu_join", 		ob);
	} else
	{
        	command("nod");
        	command("whisper"+query("id", ob)+"�����"
                        "��֮�����ǻ�ȷ����İ�\nȫ�����Ǿ�����"
                        HIW "����" NOR + WHT "ǰ�����뿪��������"
                        "������������ˣ���\n������һ�δ����"
                        "\n" NOR);
set_temp("mark/guofu_join", 1, 		ob);
	}
        return 1;
}

int accept_fight(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say ���ҹ���ȥ���ܵ�������Ϲ����ʲô��");
        	return 0;
	} else
	{
	        command("say ������û�ա�\n");
        	return 0;
	}
}

int accept_hit(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say ���ҹ���ȥ���ܵ�������Ϲ����ʲô��");
        	return 0;
	} else
	{
	        command("say ������\n");
        	kill_ob(ob);
        	return 1;
	}
}

int accept_kill(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say ���ҹ���ȥ���ܵ�������Ϲ����ʲô��");
                return notify_fail("�㻹�ǲ�Ҫ�������Ϊ�á�\n");
	} else
	{
	        command("say ������\n");
        	kill_ob(ob);
        	return 1;
	}
}

int accept_touxi(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say ���ҹ���ȥ���ܵ�������Ϲ����ʲô��");
                return notify_fail("�㻹�ǲ�Ҫ�������Ϊ�á�\n");

	} else
	{
	        command("say ������\n");
        	kill_ob(ob);
        	return 1;
	}
}

void recover()
{
        mapping p;

        clear_condition(0);
        p = query_entire_dbase();
        p["eff_qi"] = p["max_qi"];
        p["qi" ] = p["max_qi"];
        p["eff_jing"] = p["max_jing"];
        p["jing" ] = p["max_jing"];
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

void unconcious()
{
        die();
}

void die()
{
        message_vision(HIW "\n$N" HIW "�������˼���������ɫ������"
                       "�ö��ˡ�\n" NOR, this_object());
        recover();
}