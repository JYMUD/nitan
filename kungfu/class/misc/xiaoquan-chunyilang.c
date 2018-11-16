#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// XСʱ�����
#define UPDATE_TIME          36 * 3600
// ���ֵص�
#define UPDATE_PLACE         "/d/beijing/di_dajie1"
// BOSS�ļ�
#define BOSS_FILE            "/kungfu/class/misc/xiaoquan-chunyilang"

// ������ߺ����κν���
#define MAX_EXP              100000000

inherit NPC;

void create()
{
        set_name(HIM "СȮ����һ��" NOR, ({ "xiaoquan yilang boss",}));
        set("title", HIC "���Է�ɣ�Ĵ̿�" NOR);
        set("gender", "����");
        set("age", 42);
        set("long", @LONG
����һλ���Է�ɣ�Ĵ̿ͣ���˵������ɱ����ԭ͢��Ա�ġ�
LONG);
        set("attitude", "friendly");
        set("str", 31);
        set("int", 30);
        set("con", 30);
        set("dex", 46);
        set("per", 20);
        set("shen_type", 0);

        set("qi", 24000000);
        set("max_qi", 24000000);

        set("jing", 4000000);
        set("max_jing", 4000000);
        set("jingli", 4000000); 
        set("max_jingli", 4000000); 

        set("neili", 45000); 
        set("max_neili", 45000); 
        set("jiali", 2200); 
        set("combat_exp", 40000000);

	set("scborn/ok", 1);
	set("special_skill/guimai", 1);
	
        set_skill("force", 1000);
        set_skill("pixie-jian", 1000);
        set_skill("surge-force", 1000);
        set_skill("liumai-shenjian", 1000);
        set_skill("sword", 1000);
        set_skill("finger", 1000);
        set_skill("whip", 1000);
        set_skill("dodge", 1000);
        set_skill("parry", 1000);
        set_skill("unarmed", 1000);
        set_skill("strike", 1000);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1000);
        set_skill("throwing", 1000);
        set_skill("jueqing-quyu", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 1000);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",10000);
        set_temp("apply/defense", 10000);
        set_temp("apply/damage", 6000);
        set_temp("apply/unarmed_damage", 6000);
        set_temp("apply/armor", 6000);
        set_temp("apply/fy", 10);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.duo and sword.gui") :),
                (: command("perform sword.pi and sword.po") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.jian twice" :),
                (: perform_action, "finger.tian twice" :),
        }) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;	
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(5 + random(6));
	me->receive_wound("qi", 5500 + random(5600), ob);
        return HIY "$N" HIY "ŭ��һ�����������������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)						
		set("neili", query("max_neili"));

	return ::heart_beat();
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
        int weiwang;            // ��Ҫ�Ϸֵ�����
        int gongxian;           // ����
        int tihui;              // ���
        int score;              // ��Ҫ�Ϸֵ�����
        object *t;              // ɱ���ҵ��˵Ķ����б�
        object tob;
        int ysg;
        int i;

        // ���影����Ʒ�б�
	// ����  MAX_POINT ��֮ X
	mixed oblist = ([
			"/clone/misc/boss_item/ansha-mingdan"        :         240,			
			"/clone/armor/mingwang-xiang"                :         100,
			"/clone/armor/shougu"                        :         100,
			"/clone/armor/fusang/shenxing-xue"           :         200,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;

	        // ��ֱֹ��call_die()
		if (query("qi") > 500000)
		{
			revive();
			return;
		}

                // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
                if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
			//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
			destruct(this_object());
			return;
		}

                t = dob->query_team();

	        if (objectp(dob) && environment(dob) == environment(this_object()))
	        {
	                exp = 150000 + random(240000);
	                pot = 220000 + random(300000);
	                gongxian = 4400 + random(8200);
	                tihui = 20000 + random(25000);
			n = 0;
	                n = sizeof(t);

	                if (! n || n < 3)
	                {
	                       exp /= 3;
	                       pot /= 3;
	                       weiwang /= 3;
	                       score /= 3;
	                       tihui = 0;	                       
	                }

			if (n >= 3)
			{
				exp /= n;
				pot /= n;			
			}
	
			if (n)
			{				
				foreach(tob in t)
				{
					
					if (objectp(tob) && living(tob))
					{
						if (tob->query("combat_exp") >= MAX_EXP)continue;
						if (environment(tob) == environment(dob))
							GIFT_D->delay_bonus(tob,
								([ "exp"      : exp + ((tob == dob) ? 30000 : 0),
								   "pot"      : pot + ((tob == dob) ? 30000 : 0),
								   "mar"      : tihui + ((tob == dob) ? 3000 : 0),
								   //"gongxian" : tob->query("family/family_name") == "������" ? gongxian : 0,
								   "prompt"   : "��Ķ�����" + name() + "֮��"]), 999);
	
					}
				}
			}
			else
			{
				if (dob->query("combat_exp") < MAX_EXP)
					GIFT_D->delay_bonus(dob,
						 ([ "exp"      : exp,
					    	    "pot"      : pot,
					    	    "prompt"   : "���ڴ��" + name() + "֮��"]), 999);
			}
	
	        }
		
	        // һ�����ʵ���Ʒ��ɱ�ҵ�������dob
		if (objectp(dob) && environment(dob) == environment(this_object()) && 
		    dob->query("combat_exp") < MAX_EXP)
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
	        if (0)
	        {
	        	command("chat* heng");
		}/*
		else
		{
			message_vision(HIG "��Ȼ�䣬$N " HIG " ���һ���������Գ�һ�ź�ɫС�裬��ʱ����һƬ���� ...\n" NOR, 
			               this_object());
			command("chat �ߣ����С���������������ˣ���ǣ�");
			CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + name() + HIM "�ӹ�Ĺ�е����䱦�󣬶�·���ӡ�" NOR);
		}
*/
		// ���ø���
		//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
		// 1/1000���ʵ�������ͭ��
		if (random(1000) < 1)
		{
			object ob_tongren;
			ob_tongren = new("/clone/fam/item/wuming-tongren");			
			message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
			ob_tongren->set("who_get/id", "NONE");
			ob_tongren->set("who_get/time", time() + 30); // 30���ڶ����ܼ�ȡ		
			ob_tongren->move(environment(this_object()));
		}
		
		// ��������Ʒ��ͳһ����giftd�ӿ�
		GIFT_D->fuben_boss_gift(this_object());	
				
		destruct(this_object());
	
	        return;
}

void remove()
{
	MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
	return;
}
