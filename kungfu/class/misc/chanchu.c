// nanhai.c

#include <ansi.h>

#define MAX_POINT     100
#define MEMBER_D      "/adm/daemons/memberd"

inherit NPC;

void create()
{
	set_name(HIW "ǧ�����" NOR, ({ "qiannian chanchu", "qiannian", "chanchu" }) );
	set("gender", "����");
	set("age", 1000);
	set("long", @LONG
����һֻ�޴����ܣ�����������ɫ���������ǿ��¡�
LONG );
	set("combat_exp", 2000000000);
	set("shen_type", 0);
	set("attitude", "heroism");
        set("max_neili", 2000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 10000000);
	set("eff_qi", 10000000);
        set("qi", 10000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

        set("no_nuoyi", 1); // ����Ų��Ӱ��

        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 200);

		set_skill("unarmed", 1500);
		set_skill("sword", 1500);
		set_skill("parry", 1500);
		set_skill("dodge", 1500);
		set_skill("force", 1500);

        set("jiali", 1000);

        set_temp("apply/attack", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/damage", 1000);
        set_temp("apply/armor", 1500);

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
        message_vision("$Nһ���ֽУ����˹�����\n",
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
	ob->start_busy(5 + random(5));
	me->receive_wound("qi", 3000 + random(3000), ob);
        return HIY "$N" HIY "��Χ�����뵣�ֱ�Ƶ�$n" HIY "ͷ��Ŀѣ��\n" NOR;
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
		if (query("qi") > 100000)
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
        int weiwang;            // ��Ҫ�Ϸֵ�����
        int score;              // ��Ҫ�Ϸֵ�����
        object *t;              // ɱ���ҵ��˵Ķ����б�
        object tob;
        int i;

        // ���影����Ʒ�б�
		// ����  X / ���֮һ
		mixed oblist = ([
			"/clone/armor/fenghuang-chai2"           :        	1,
			"/clone/armor/haizhi-xin2"               :        	1,
			"/clone/armor/shengling-yaodai3"         :          1,
			"/clone/armor/shangu-zhixing3"           :          1,
			"/clone/fam/enchase/shenglong-zhihun"    :          1,
			"/clone/fam/enchase/shenglong-zhiyan"    :          1,

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
				message_vision("shit\n", this_object());
				destruct(this_object());
				return;
		}

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 2000 + random(5000);
                pot = 4500 + random(3000);
                weiwang = 1000 + random(3000);
                score = 2000 + random(2000);
				n = 0;
                n = sizeof(t);
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       weiwang /= 3;
                       score /= 3;
                }

				if (n >= 3)
				{
					exp /= n;
					pot /= n;
					weiwang /= n;
					score /= n;
				}

				if (n)
				{				
					foreach(tob in t)
					{
						  if (objectp(tob) && living(tob))
						 {
								   GIFT_D->delay_bonus(tob,
								          ([ "exp"      : exp + ((tob == dob) ? 1000 : 0),
									         "pot"      : pot + ((tob == dob) ? 1000 : 0),
										     "weiwang"  : weiwang + ((tob == dob) ? 1000 : 0),
											 "score"    : score + ((tob == dob) ? 1000 : 0),
									         "prompt"   : "��Ķ���ɱ��" + name() + "֮��"]), 999);

						 }
					}
				}
				else
				{
								   GIFT_D->delay_bonus(dob,
								          ([ "exp"      : exp,
									         "pot"      : pot,
										     "weiwang"  : weiwang,
											 "score"    : score,
									         "prompt"   : "����ɱ��" + name() + "֮��"]), 999);
				}

        }

        // һ�����ʵ���Ʒ��ɱ�ҵ�������dob
		if (objectp(dob) && environment(dob) == environment(this_object()))
		{
			key_s_gift = keys(oblist);
			s_gift = key_s_gift[random(sizeof(key_s_gift))];
			gift_point = oblist[s_gift];

			// �жϼ���
			if (MEMBER_D->is_valib_member(dob->query("id")) 
				&& random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
			{
				// �����Ʒ--������Ʒֱ�ӷ���dob����
				gift_ob = new(s_gift);
				if (objectp(gift_ob))
				{
					message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR 
						           "�Ͻ�����������\n" NOR, this_object(), dob);
					tell_object(dob, BLINK + HIG "��õ���" + gift_ob->name() + BLINK + HIG "��\n" NOR);
					gift_ob->move(dob, 1);
				}
				else // ��¼֮ 
				{
					log_file("killed-gift-none", s_gift + "\n");
				}
			}
		}

        // ��ʧ
	message_vision("$N��Хһ����Ȼ��Ϊһ̲Ѫˮ��������¡�\n", this_object());

        // �ж��Ƿ����ѧ��perform tuitian
        if (dob->query_skill("jiuyin-hamagong", 1) && ! dob->query("can_perform/jiuyin-hamagong/puji"))
        {
        	dob->set("can_perform/jiuyin-hamagong/puji", 1);
        	dob->save();
        	
        	tell_object(dob, HIG "��ϲ�㣬��ͨ��ɱ��ǧ����ܣ�������˾�����󡹦�ľ���[����ʽ]!\n");
        }
        
        destruct(this_object());

        return;
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N��Хһ��������һ̲Ѫˮ��������¡�\n", this_object());
       
		destruct(this_object());
		return;
	}
}
