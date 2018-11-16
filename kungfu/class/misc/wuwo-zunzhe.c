// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 100

inherit NPC;

void create()
{
        set_name(HIY "��������" NOR, ({ "wuwo zunzhe"}) );
        set("title", HIG "���ǹ�����" NOR);
        set("long", HIR "һλ��ɫ���Ƶ����ߣ��ƺ�����һ�г������ף�\n" NOR);

        set("gender", "����");
        set("age", 49);

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              // 
              (: command("perform sword.ben twice") :), 
              (: command("perform sword.ben and sword.tian") :),
              // ����12t
              (: command("perform finger.tian twice") :), 
              (: command("perform finger.zhen and finger.jiu") :), 

              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
        }));

        setup();

        // �·�
        carry_object("/clone/cloth/bupao")->wear();
        // ����
        carry_object("/clone/weapon/fengshen-jian")->wield();

        // ���õص�
        //set("startroom", "/d/shenlong/huodong1");
}


void init_npc(object me)
{
        int max_skill, npc_level, npc_qi;
        int arg, exp, pot, mar;
        
        //me = find_player("rcwiz");

        max_skill = WAR_D->max_skills_level(me);

        
        set("me", me);
        set("combat_exp", me->query("combat_exp"));

        if (max_skill <= 100)
        {
                npc_qi = 3000000;
        }
        else
        if (max_skill <= 200)
        {
                npc_qi = 4000000;
        }
        else
        if (max_skill <= 300)
        {
                npc_qi = 5000000;
        }
        else 
        if (max_skill <= 400)
        {
                npc_qi = 6000000;
        }
        else 
        if (max_skill <= 500)
        {
                npc_qi = 8000000;
        }
        else 
        if (max_skill <= 750)
        {
                npc_qi = 10000000;
        }
        else
        if (max_skill <= 1000)
        {
                npc_qi = 15000000;
        }
        else
        if (max_skill <= 1500)
        {
                npc_qi = 20000000;
        }
        else 
        if (max_skill <= 2000)
        {
                npc_qi = 25000000;
        }
        else 
        if (max_skill <= 2500)
        {
                npc_qi = 30000000;
        }
        else 
        if (max_skill <= 3000)
        {
                npc_qi = 40000000;
        }
        else 
        if (max_skill <= 3500)
        {
                npc_qi = 50000000;
        }
        else 
        if (max_skill <= 4000)
        {
                npc_qi = 60000000; 
        }
        else 
        if (max_skill <= 4500)
        {
                npc_qi = 70000000;
        }
        else 
        if (max_skill <= 5000)
        {
                npc_qi = 80000000;
        }
        else 
        if (max_skill <= 5500)
        {
                npc_qi = 100000000;      // 1E
        }
        else 
        if (max_skill <= 6000)
        {
                npc_qi = 120000000;
        }
        else 
        if (max_skill <= 6500)
        {
                npc_qi = 140000000;
        }
        else 
        if (max_skill <= 7000)
        {
                npc_qi = 160000000;
        }
        else 
        if (max_skill <= 7500)
        {
                npc_qi = 180000000;
        }
        else 
        if (max_skill <= 8000)
        {
                npc_qi = 200000000;
        }
        else
        {
                npc_qi = 250000000; // 2.5E
        }
                        
        // ��NPC_qi����
        npc_qi -= npc_qi / 2; // ����50%

        reset_eval_cost();

        set("max_qi", npc_qi);
        set("eff_qi", npc_qi);
        set("qi", npc_qi);

        // �̶�ֵ
        set("str",50);
        set("int", 200);
        set("con", 200);
        set("dex", 50);
        set("shen", 0);
        set("scborn/ok", 1);
        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000); 
        set("jingli", 1000000000);  
        set("neili", 10000000);
        set("max_neili", 10000000);
        set("jiali", 1000);
        set("no_nuoyi", 1); // ����Ų��Ӱ��
        set_temp("apply/qy", 20);  // ����
        set_temp("apply/fy", 20);  // ��Ե

        npc_level = max_skill; 
        
        // ��npc_level���� 
        npc_level -= npc_level / 5; // ����20%

        set_skill("unarmed", npc_level);
        set_skill("finger", npc_level);
        set_skill("claw", npc_level);
        set_skill("strike", npc_level);
        set_skill("hand", npc_level);
        set_skill("cuff", npc_level);
        set_skill("parry", npc_level);
        set_skill("dodge", npc_level);
        set_skill("force", npc_level);
        set_skill("sword", npc_level);
        set_skill("blade", npc_level);
        set_skill("zuoyou-hubo", 2500);

        set_skill("daojian-guizhen", npc_level);
        set_skill("jiuyang-shengong", npc_level);
        set_skill("yinyang-shiertian", npc_level);
        set_skill("qiankun-danuoyi", npc_level);
        set_skill("martial-cognize", npc_level);
        set_skill("qiankun-danuoyi", npc_level);
        set_skill("lingbo-weibu", npc_level);
        set_skill("literate", 4000);
        set_skill("daojian-xiaotianwai", 500);
        set_skill("jingluo-xue", npc_level);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "yinyang-shiertian");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "daojian-guizhen");
        map_skill("blade", "daojian-guizhen");

        prepare_skill("finger", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");

        // ����
        exp = max_skill * 10;
        pot = max_skill * 20;
        mar = max_skill * 5;

        set("exp", exp);
        set("pot", pot);
        set("mar", mar);

        arg = max_skill / 500;
        if (arg > 10)arg = 10;
        set_temp("apply/attack", max_skill * arg);
        set_temp("apply/unarmed_damage", max_skill * arg);
        set_temp("apply/damage", max_skill * arg); 
        set_temp("apply/armor", max_skill * arg);
}

void init()
{
        object me;

        me = this_player();

        me->set("env/combatd", 4);
        command("bow");
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void unconcious()
{
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // �������NPC����
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
        int mar;                //  ��Ҫ�Ϸֵ����
        int i;
        object gift_ob, gift_ob2, gift_ob3, ob_tys;
        string s_gift, *key_s_gift;
        int gift_point, ran;

        // ���影����Ʒ�б�
        // ����  X / �ٷ�֮
        mixed oblist = ([
                "/clone/fam/max/naobaijin"               : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,           
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,           
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,                                                                         
        ]);


        // dob ������������ init_npc(me)��ʱ���Ѿ�����
        dob = query("me");

        if (! dob)destruct(this_object());
        
        // ��ֱֹ��call_die()
        if (query("qi") > 500000)
        {
                revive();
                return;
        }

        if (1)
        {
                exp = query("exp");
                pot = query("pot");
                mar = query("mar");

                if (MEMBER_D->is_valib_member(dob->query("id")))
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp + exp / 10,
                                           "pot"      : pot + pot  / 10,
                                           "mar"      : mar + mar/ 10, 
                                           "prompt"   : "����սʤ" + name() + HIG "֮��"]), 999);
                }

                else
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp,
                                           "pot"      : pot,
                                           "mar"      : mar,
                                           "prompt"   : "����սʤ" + name() + HIG "֮��"]), 999); 
                }
        }

        // 50%����Ʒ
        if (random(100) < 25)
        {
                key_s_gift = keys(oblist);

                // 100%���ٱ�һ��
                if (1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + 
                                               gift_ob->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());
                                gift_ob->set("who_get/id", "NONE");
                                gift_ob->set("who_get/time", time() + 30); // 30���ڶ����ܼ�ȡ
                                gift_ob->move(environment(this_object()));
                        }
                        else // ��¼֮
                        {
                                //log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
                
                // 20%������׷��һ����Ʒ
                if (random(10) < 2)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob2 = new(s_gift);
                        if (objectp(gift_ob2))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + 
                                               gift_ob2->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());
                                gift_ob2->move(environment(this_object()));
                        }
                        else // ��¼֮
                        {
                                //log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
        }
        
        // 50%���ʵ�����Ӣʯͷ
        if (random(100) < 25)
        {
                ob_tys = new("/clone/fam/item/tieying-shi");
                ob_tys->set_amount(1 + random(5));
                if (objectp(ob_tys))
                {
                        message_vision(HIG "��~~һ������$N" HIG "���ϵ���" + HIY + 
                                       sprintf("%d", ob_tys->query_amount()) + HIG "��" + 
                                       ob_tys->name() + HIG "�����ڵ��ϡ�\n" NOR, this_object());
                        ob_tys->move(environment(this_object()));
                }
                else // ��¼֮
                {
                        log_file("gift-none", "��Ӣʯ from " + __FILE__ + "\n");
                }               
                
        }
        
/*      
        // 5/100���ʵ�������ͭ��
        if (random(100) < 5)
        {
                object ob_tongren;
                ob_tongren = new("/clone/fam/item/wuming-tongren");
                message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
                ob_tongren->set("who_get/id", "NONE");
== δ����� 95% == (ENTER ������һҳ��q �뿪��b ǰһҳ)
                ob_tongren->set("who_get/time", time() + 30); // 30���ڶ����ܼ�ȡ
                ob_tongren->move(environment(this_object()));
        }
   */
   
        // Ϊ������ڰ����ۻ�����
        BUNCH_D->add_points(dob);
        
        destruct(this_object());
        return ;
}  
