// nanhai.c

#include <ansi.h>

#define MAX_POINT     1000
#define MEMBER_D      "/adm/daemons/memberd"

inherit NPC;

void create()
{
	set_name(HIY "�߲�" HIM "������" NOR, ({ "qicai liulishou", "qicai", "liulishou" }) );
	set("title", HIW "ʥ��" HIR "����" NOR);
	set("gender", "����");
	set("age", 8888);
	set("long", @LONG
����һֻ�������ع��ޣ�ȫ��ó��߲�֮ɫ��ͷ����С��һ�Ի�Բ����
����˸�����˵Ĺ�â��
LONG );
	set("combat_exp", 2000000000);
	set("shen_type", 0);
	set("attitude", "heroism");
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 900000000);
	set("eff_qi", 900000000);
        set("qi", 900000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

	set("no_nuoyi", 1); // ����Ų��Ӱ��

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 300);

	set_skill("unarmed", 4000);
	set_skill("sword", 4000);
	set_skill("parry", 4000);
	set_skill("dodge", 4000);
	set_skill("force", 4000);

        set("jiali", 1000);

        set_temp("apply/attack", 150000);
        set_temp("apply/unarmed_damage", 100000);
	set_temp("apply/damage", 100000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

		setup();
}

int accept_fight(object ob)
{
        message_vision("$Nһ���޺����˹�����\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
		ob->start_busy(20 + random(10));
		me->receive_wound("qi", 5000 + random(3000), ob);
        return HIY "$N" HIY "��Χ�������ƣ�ֱ�Ƶ�$n" HIY "ͷ��Ŀѣ��\n" NOR;
}

void heart_beat()
{
		if (query("neili") < 1)
			set("neili", query("max_neili"));

		::heart_beat();
}

void unconcious()
{
	    // ��ֱֹ��call_die()
		if (query("qi") > 500000)
		{
			revive();
			return;
		}
	
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // �������NPC����
        int n;                  // ���Խ������˵���Ŀ
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
        int tihui;              // ��Ҫ�Ϸֵ����
        int weiwang;            // ��Ҫ�Ϸֵ�����
        int score;              // ��Ҫ�Ϸֵ�����
        object *t;              // ɱ���ҵ��˵Ķ����б�
        object tob;
        int i;

        // ���影����Ʒ�б�
		// ����  X / ���֮һ
		mixed oblist = ([

		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;
		
	    // ��ֱֹ��call_die()
		if (query("qi") > 100000)
		{
			revive();
			return;
		}

        // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
				destruct(this_object());
				return;
		}

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 1000000 + random(1500000);
                pot = 1000000 + random(1000000);
                tihui = 150000 + random(70000);
                //weiwang = 100000 + random(300000);
                //score = 200000 + random(200000);
		n = 0;
                n = sizeof(t);
                
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       tihui /= 5;
                       //weiwang /= 3;
                       //score /= 3;
                }

		if (n >= 3)
		{
			exp /= n;
			pot /= n;
			tihui /= n;
			//weiwang /= n;
			//score /= n;
		}

		if (n)
		{				
			foreach(tob in t)
			{
				  if (objectp(tob) && living(tob))
				 {
				 		if (environment(tob) == environment(dob))
						   GIFT_D->delay_bonus(tob,
						          ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),
							     "pot"      : pot + ((tob == dob) ? 50000 : 0),
						             //"weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),
							     //"score"    : score + ((tob == dob) ? 50000 : 0),
							      "mar"      : tihui + ((tob == dob) ? 10000 : 0),
							     "prompt"   : "��Ķ�����" + name() + "֮��"]), 999);

				 }
			}
		}
		else
		{
						   GIFT_D->delay_bonus(dob,
						          ([ "exp"      : exp,
							     "pot"      : pot,
							     //"weiwang"  : weiwang,
						             //"score"    : score,
						             "mar"      : tihui + ((tob == dob) ? 10000 : 0),
							     "prompt"   : "���ڴ��" + name() + "֮��"]), 999);
		}

        }
        //25%���ʵ����߲�����ѥ
 	if (objectp(dob) && environment(dob) == environment(this_object()) && random(4) == 1)
	{
		gift_ob = new("/clone/armor/qicai-xue");
		message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR 
			           "�Ͻ�����������\n" NOR, this_object(), dob);
		tell_object(dob, BLINK + HIG "��õ���" + gift_ob->name() + BLINK + HIG "��\n" NOR);
		gift_ob->move(dob, 1);
	}

        // ��ʧ
        command("chat �������˶���֮��ʵ��������ûȤ��");
	message_vision("$N��Хһ��������һ�Ż��棬��ʧ����ʡ�\n", this_object());
        CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + name() + HIM "��һȺ������ʿ��ܣ����˶��顣" NOR);
                        
	destruct(this_object());

        return;
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N��Хһ��������һ�Ż��棬��ʧ����ʡ�\n", this_object());
		destruct(this_object());
		return;
	}
}
