 // ouyangfeng.c

#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// XСʱ�����
#define UPDATE_TIME          3 * 3600
// ���ֵص�
#define UPDATE_PLACE         "/d/penglai/fanchendao"
// BOSS�ļ�
#define BOSS_FILE            "/kungfu/class/misc/liuer-mihou"

// ������ߺ����κν���
#define MAX_EXP              10000000

inherit NPC;

void create()
{
        set_name(HIC "����⨺�" NOR, ({ "liuer mihou", "liuer", "mihou" }));
        set("long", HIC "����һֻ��ò���ص�⨺�Ѿ����������Σ��������������������׶Ը���\n" NOR);

        set("gender", "����");
        set("age", 1200);
        set("nickname", HIR "���������˵�" NOR);
        set("shen_type", 0);
        set("attitude", "peaceful");

        set("str", 120);
        set("int", 60);
        set("con", 60);
        set("dex", 160);

        set("qi", 9000000);
        set("max_qi", 9000000);

        set("jing", 2000000);
        set("max_jing", 2000000);
        set("jingli", 2000000); 
        set("max_jingli", 2000000); 

        set("neili", 50000); 
        set("max_neili", 50000); 
        set("jiali", 600); 
        set("combat_exp", 8000000);

        set_skill("force", 400);
        set_skill("unarmed", 400);
        set_skill("dodge", 400);
        set_skill("parry", 400);
        set_skill("cuff", 400);
        set_skill("finger", 400);
        set_skill("training", 400);          

        set_skill("jiuyin-hamagong", 400); 
        set_skill("baituo-xinfa", 400);          
 
        set_skill("staff", 400);
        //set_skill("training", 340);
        set_skill("poison", 400);

        set_skill("shedu-qiqiao", 400);
        set_skill("hamagong", 400);
        set_skill("baituo-xinfa", 400);
        set_skill("chanchu-bufa", 400);
        set_skill("lingshe-quan", 400);
        set_skill("lingshe-zhangfa", 400);
        set_skill("baibian-daxue", 400);
        set_skill("guzheng-jifa", 400);
        set_skill("xiyu-tiezheng", 400);
        set_skill("wushe-qu", 400);
        set_skill("literate", 400);
        set_skill("medical", 400);
        set_skill("baituo-michuan", 400);
        set_skill("martial-cognize", 400);

        map_skill("dodge", "chanchu-bufa");
        map_skill("force", "jiuyin-hamagong"); 
        map_skill("unarmed", "jiuyin-hamagong"); 
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("unarmed", "jiuyin-hamagong"); 

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.qian" :),
                (: perform_action, "staff.bite" :),  
                (: perform_action, "unarmed.puji" :),  
                (: perform_action, "unarmed.zhen" :), 
                (: perform_action, "unarmed.puji" :), 
                (: exert_function, "yijin" :), 
        }));

        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 2000);

        setup();
        
        carry_object("/clone/weapon/taomuzhang")->wield(); 
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/xianlv")->wear();
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
	me->receive_wound("qi", 900 + random(900), ob);
        return HIY "$N" HIY "���һ����ƴ�����������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)						
		set("neili", query("max_neili"));

	::heart_beat();
}

void unconcious()
{/*
	// ��ֱֹ��call_die()
	if (query("qi") > 60000)
	{
		revive();
		return;
	}
	*/
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
			"/clone/money/gold"                     :        	200,
			"/clone/money/yuanbao"                  :        	100,			
			"/clone/fam/pill/renshen4"               :        	30,
			"/clone/armor/zijinhua-erhuan2"          :        	30,
			"/clone/armor/yecha3"                    :              220,
			"/clone/fam/max/naobaijin"               :              20,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;
/*
	        // ��ֱֹ��call_die()
		if (query("qi") > 60000)
		{
			revive();
			return;
		}
*/
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
	                exp = 90000 + random(80000);
	                pot = 200000 + random(80001);
	                gongxian = 8400 + random(8200);
	                tihui = 9100 + random(9800);
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
								([ "exp"      : exp + ((tob == dob) ? 3000 : 0),
								   "pot"      : pot + ((tob == dob) ? 3000 : 0),
								   "mar"      : tihui + ((tob == dob) ? 1000 : 0),
								   "gongxian" : tob->query("family/family_name") == "������" ? gongxian : 0,
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
	        if (1)
	        {
	        	command("chat* sigh");
	        	command("chat �������һ���Ӧ���ٻص���ɽ������һǧ����˵...");			
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

		// 1/500���ʵ�������ͭ��
		if (random(500) < 1)
		{
			object ob_tongren;
			ob_tongren = new("/clone/fam/item/wuming-tongren");			
			message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
			ob_tongren->set("who_get/id", "NONE");
			ob_tongren->set("who_get/time", time() + 30); // 30���ڶ����ܼ�ȡ		
			ob_tongren->move(environment(this_object()));
		}

		destruct(this_object());
	
	        return;
}

void remove()
{
	if (GIFT_D->is_open_pld())MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
	return ::remove();
}
