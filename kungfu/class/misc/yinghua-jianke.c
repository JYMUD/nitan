#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// XСʱ�����
#define UPDATE_TIME          24 * 3600
// ���ֵص�
#define UPDATE_PLACE         "/d/fuzhou/zhongzhou"
// BOSS�ļ�
#define BOSS_FILE            "/kungfu/class/misc/yinghua-jianke"

// ������ߺ����κν���
#define MAX_EXP              50000000

inherit NPC;

void create()
{
        set_name(HIM "ӣ������" NOR, ({ "yinghua jianke boss",}));
        set("title", HIW "���Է�ɣӣ��֮���" NOR);
        set("gender", "����");
        set("age", 22);
        set("long", @LONG
����һλ���Է�ɣ�Ľ��ͣ���ɫ�ĳ���������ӣ���ı�ǡ�
LONG);
        set("attitude", "friendly");
        set("str", 31);
        set("int", 30);
        set("con", 30);
        set("dex", 46);
        set("per", 20);
        set("shen_type", 0);

        set("qi", 12000000);
        set("max_qi", 12000000);

        set("jing", 4000000);
        set("max_jing", 4000000);
        set("jingli", 4000000); 
        set("max_jingli", 4000000); 

        set("neili", 35000); 
        set("max_neili", 35000); 
        set("jiali", 1200); 
        set("combat_exp", 20000000);

	set("scborn/ok", 1);
	set("special_skill/guimai", 1);
	
        set_skill("force", 1000);
        set_skill("pixie-jian", 800);
        set_skill("surge-force", 800);
        set_skill("liumai-shenjian", 800);
        set_skill("sword", 800);
        set_skill("finger", 800);
        set_skill("whip", 800);
        set_skill("dodge", 800);
        set_skill("parry", 800);
        set_skill("unarmed", 800);
        set_skill("strike", 800);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1000);
        set_skill("throwing", 800);
        set_skill("jueqing-quyu", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 700);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",5000);
        set_temp("apply/defense", 5000);
        set_temp("apply/damage", 4000);
        set_temp("apply/unarmed_damage", 4000);
        set_temp("apply/armor", 4000);
        set_temp("apply/fy", 5);

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
	me->receive_wound("qi", 2500 + random(2600), ob);
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
	if (query("qi") > 200000)
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
			"/clone/misc/boss_item/fengjing-hua"    :         240,			
			"/clone/armor/yinghua-fu"               :         100,
			//"/clone/armor/fusang/heima-yi"        :         200,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;

	        // ��ֱֹ��call_die()
		if (query("qi") > 200000)
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
	                exp = 120000 + random(180000);
	                pot = 180000 + random(200000);
	                gongxian = 4400 + random(8200);
	                tihui = 12000 + random(18000);
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
	        	command("chat* sigh");
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
