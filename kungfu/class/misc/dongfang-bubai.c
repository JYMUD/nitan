#include <ansi.h>

#define MAX_POINT 100

inherit BOSS;

void damage_all();
void check_weapon();

void create()
{
        set_name(HIR "��������" NOR, ({ "dongfang bubai", "dongfang", "bubai" }) );
        set("title", HIG "Ӱħ" NOR);
        set("long", HIR "��������һ��δ�����ܹ�����������ͤ������ģ�������\n"
                        "�����е��ˣ��ؽ����������¡��˽�ӹʮ�Ĳ��������ɫ��\n"
                        "�������֮һ�����ڶ������֮�¡�\n" NOR);

        set("gender", "����");
        set("age", 39);

        set("str", 800);
        set("int", 800);
        set("con", 800);
        set("dex", 800);

        set("shen", 0);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/reduce_busy", 100);
        set_temp("apply/avoid_forget", 100);

        set("reborn/times", 1);

        set("max_qi", 2100000000);
        set("eff_qi", 2100000000);
        set("qi", 2100000000);

        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000); 
        set("jingli", 1000000000);  

        set("neili", 200000000);
        set("max_neili", 1000000);
        set("jiali", 50000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 5000);
        set_skill("finger", 5000);
        set_skill("claw", 5000);
        set_skill("strike", 5000);
        set_skill("hand", 5000);
        set_skill("cuff", 5000);
        set_skill("parry", 5000);
        set_skill("dodge", 5000);
        set_skill("force", 5000);
        set_skill("sword", 5000);
        set_skill("blade", 5000);
        set_skill("zuoyou-hubo", 2500);

        set_skill("kuihua-mogong", 5000);
        set_skill("qiankun-danuoyi", 5000);
        set_skill("martial-cognize", 5000);
        set_skill("literate", 5000);
        set_skill("huajia-su", 800);

        set_skill("jingluo-xue", 4000);

        set("no_nuoyi", 1); // ����Ų��Ӱ��
        
        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("strike", "kuihua-mogong");
        map_skill("hand", "kuihua-mogong");
        map_skill("cuff", "kuihua-mogong");
        map_skill("claw", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");
        
        prepare_skill("unarmed", "kuihua-mogong");
        prepare_skill("finger", "kuihua-mogong");

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: perform_action, "unarmed.fenshen" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),

              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "roar" :), 
              (: exert_function, "recover" :),   
              (: exert_function, "recover" :), 
              (: exert_function, "dispel" :), 
              (: check_weapon :),

        }));

        set("my_life", 1); // ����Ѫ����10%��ʱ����һ�Σ����øò���Ϊ0

        setup();

        // �·�
        carry_object("/kungfu/class/riyue/dongfang/changpao")->wear();

        // ����
        carry_object("/kungfu/class/riyue/dongfang/zhen")->wield();

        // ���õص�
        //set("startroom", "/d/shenlong/huodong1");
}

// ȫ���˺� ����һ��
/*
�������ܾ߱�����һ�������������ȫ��100%���У���Ѫ������80%
-- ��װ����߱��������ã����£�$HIG$
   -= ͨ����װ: 50%���ʵ�������һ����ͬʱ����һ��������ʧ�ܣ���Ѫ������50%$HIM$
   -= �����װ: �߱�ͨ����װ�����ԡ�ͬʱ�����ж������ܺ����׷��һ���˺���
                æ��Ч����
                ���籾�����ж��������˺�Ϊ10������׷��10���˺���ͬʱ����
                æ��5��10�롣$HIR$
   -= �컯��װ:90%���ʵ�������һ����ͬʱ����һ��������ʧ�ܣ���Ѫ������30%
               ���ж������ܺ����׷�Ӷ����˺���æ��Ч�������籾�����ж�����
               ���˺�Ϊ10������׷��20���˺���ͬʱ����æ��5��10�롣
               ���ж������ܺ�70%׷�ӷ���10�롣$NOR$
*/
void damage_all()
{
        string msg;
        object *obs;
        int i, tzlv;
        
        if( !environment() )
        {
                set_heart_beat(0);
                return;
        }
        
        msg = HIG "$N" HIG "һ����Х������������Ӱ�������Ŵ���˷��ļ�Х��������Ӱ�����ĵ����ĵ�"
                  "�����˵���ʮ��������ʮ��������ʮ�ĵ�������ǧ��Ӱ�������ܣ�����ޱȣ����ȹ��졣"
                  "��Ȼ�䣬���һ�����������������˷�����������������˶���Ϣ��\n" NOR;
        
        message_vision(sort_msg(msg), this_object());
        
        obs = all_inventory(environment(this_object()));
        for (i = 0; i < sizeof(obs); i++)
        {
                reset_eval_cost();
                
                if (! obs[i]->is_character() || obs[i] == this_object())
                        continue;

                tzlv = to_int(query_temp("modequip_itemmake_level", obs[i])); 
                // ��װ�ȼ���2���µ�100%�յ�80%����Ѫ�����˺�
                // ���������϶�û����װ��Ҳ��100%����
                if ( tzlv < 2 || ! playerp(obs[i]))
                {
                        set("last_damage_from", this_object(), obs[i]);
                        obs[i]->receive_wound("qi",query("max_qi", obs[i])/5*4,this_object());
                        message_vision("$N" HIY "������֣��Ѿ������м�֮�����������봩�ض�����"
                                           "��Ȼ���һ����Ѫ�����˼������������ˣ��޷�������\n" NOR, obs[i]);
                        obs[i]->start_busy(10);
                }
                else if (tzlv == 2)
                {
                        // 50%��������δ�ɹ������˺�Ϊ50%
                        if (random(2))
                        {
                                message_vision("$N" HIG "������֣��Ѿ������м�֮����ͻȻȫ��һ���̹����֣���"
                                                   "���ġ�ͨ����װ���������˺�ȫ��������\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "������֣��Ѿ������м�֮�����������봩�ض�����"
                                                   "��Ȼ���һ����Ѫ��\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }
                }
                else if (tzlv == 3)
                {
                        if (random(2))
                        {
                                message_vision("$N" HIC "������֣��Ѿ������м�֮����ͻȻȫ��һ��������֣���"
                                                   "���ġ������װ���������˺�ȫ��������\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "������֣��Ѿ������м�֮�����������봩�ض�����"
                                                   "��Ȼ���һ����Ѫ��\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }                       
                }
                else if (tzlv == 4)
                {
                        
                        if (1)
                        {
                                message_vision(HIM "$N" HIM "���������һ����ɫ�Ĺ�â����������Χ�����컯��װ��"
                                                    "�������죬���������˺����������Σ�\n" NOR, obs[i]);
                        }
                        else
                        {
                                //obs[i]->set("last_damage_from", this_object());
                                //obs[i]->receive_wound("qi", obs[i]->query("max_qi")/10*3, this_object());
                                message_vision("$N" HIY "ƴ���ֿ���ȴ��Ȼ��һ�����⴩��������컯��װ����ɫ��â��"
                                               "�֣���������������˺���\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }
                }
        }
}

void heart_beat()
{
        object ob;
        
        keep_heart_beat();

        // �������perform yun������
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }
/*
        // �������
        if (! query_temp("weapon"))
        {
                ob = new("/clone/weapon/xuantie-jian");
                ob->move(this_object());
                "/cmds/std/wield"->main(this_object(), "xuantie-jian");
        }
        */
        if (random(5) == 1)check_weapon();
        
        // 5%�Ļ���ȫ��������100%���У���Ѫ������80%
        if (random(100) < 5)
        {
                damage_all();
        }
        
        return ::heart_beat();
}

// �������
void check_weapon()
{
        object me, ob;
        
        me = this_object();

        // ͬʱ��������
        set("neili", query("max_neili"));

        if (me->is_busy())me->interrupt_busy(me, 1000); 

        if (me->is_busy())me->interrupt_me(me);

        if( !query_temp("weapon", me) )
        {
                ob = new("/kungfu/class/riyue/dongfang/zhen");
                ob->move(me);
                "/cmds/std/wield"->main(me, "zhen");
        }
/*
        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);
                
                addn_temp("apply/damage", 50000, me);
                if (random(10) == 1)
                        command("perform sword.tian twice");
                else            
                        command("perform sword.po and finger.tian");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }
*/
        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // ��С���ʻָ���Ѫ
        if (random(800) == 1)
        {
                //log_file("qilin", ctime(time()) + " �ɹ��ָ���Ѫ��\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        if (me->is_busy())me->interrupt_busy(me); 

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun roar");
        }

        return;
}

void init()
{
        object me;

        me = this_player();
        
        set("env/combatd", 4, me);
        //if (! wizardp(me))this_object()->kill_ob(me);
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

void new_life()
{
        object me = this_object();
        
        // ������Ѫ
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);

        me->clear_condition();

        me->interrupt_me(this_object());

        delete_temp("no_perform", me);
        delete_temp("no_exert", me);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/qy", 70);  // ����
        set_temp("apply/fy", 70);  // ��Ե              
        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "���һ����Ŀ���ʱ����ɱ�⣡\n\n" NOR, me);
        
        return; 
}

int receive_damage(string type, int damage, object who)
{
        object ob;
        int tzlv;
        
        object me = this_object();
        
        
        // ��װ��׷���˺�
        if (objectp(who))
        {
                tzlv = 1;
                
                if (tzlv == 3)// 
                {
                        damage *= 2;
                        this_object()->start_busy(5+random(6));
                        tell_object(HIM "�������װ��׷���˺�������æ�ң�\n" NOR);
                }
                else if (tzlv == 4)
                {
                        damage *= 3;
                        start_busy(5+random(6));
                        tell_object(HIM "���컯��װ��׷���˺�������æ�ң�\n" NOR);
                        if (random(10) < 7)
                        {
                                set_temp("no_perform", 1);
                                call_out("remove_no_perform", 10);
                                tell_object(HIC "���컯��װ��׷�ӷ���10�룡\n" NOR);
                        }
                }
        }
        
        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // ����һ��
                return 0;
        }

        return ::receive_damage(type, damage, who);
}


void remove_no_perform()
{
        delete_temp("no_perform");
}

// �������
void check_life()
{
        object env;
        
        // ���life<=1������
        if (1)
        {
                message_vision(HIR "\n$N" HIR "������Х����ͤ����ȥҲ ����\n" NOR, this_object());
                // ��¼
                log_file("dongfang_die", "���������� " + ctime(time()) + " ��ɱ����\n");

                destruct(this_object());
        }
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
        object ob;
        int mar;                //  ��Ҫ�Ϸֵ����
        int i;

        // ���影����Ʒ�б�
        // ����  X / �ٷ�֮
        mixed oblist = ([
                "/clone/fam/super/dugu/bldan"        : 1,
                "/clone/fam/super/dugu/bhxdan"        : 1,
                "/clone/fam/super/dugu/bjxcao"        : 1,
                "/clone/fam/super/dugu/hlzhi"        : 1,
                "/clone/fam/super/dugu/jzdan"        : 1,
                "/clone/fam/super/dugu/qhcao"        : 1,
                "/clone/fam/super/dugu/qhdan"        : 1,
                "/clone/fam/super/dugu/sxguo"        : 1,
                "/clone/fam/super/dugu/tldan"        : 1,
                "/clone/fam/super/dugu/xhcao"        : 1,
                "/clone/fam/super/dugu/xmgu"        : 1,
                "/clone/fam/super/dugu/qlndan"        : 1,
        ]);

        object gift_ob, gift_ob2, gift_ob3, gift_ob4;
        string s_gift, *key_s_gift;
        int gift_point, ran;
                              
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) { 
                full_self(); 
                return; 
        }

        // �����δ������������һ��
        if (query("my_life"))
        {
                new_life();
                return;
        }

        // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        // ����ҵ�
        if (! objectp(dob))dob = query_defeated_by();

        if (! objectp(dob))
        {
                // ����������麯��
                check_life();
                return;
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))                                                              
        {
                exp = 40000 + random(40000);
                pot = 40000 + random(40000);
                weiwang = 6000 + random(9000);
                score = 6000 + random(6000);
                mar = 12000 + random(12000);
                n = 0;
                
                n = sizeof(t);
                if (! n || n < 3)                                                                                                        
                {
                       exp /= 5;                                                                                                         
                       pot /= 5;                                                                                                         
                       weiwang /= 3;
                       score /= 3;
                       mar /= 5;
                }

                if (n >= 3)
                {
                        exp /= n;
                        pot /= n;
                        weiwang /= n;
                        score /= n;
                        mar /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {       
                                        // ��Ա���������10%
                                        if( MEMBER_D->is_valib_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + exp * 1 / 10 + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + pot * 1 / 10 / 10 + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + weiwang * 1 / 10 + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + score * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "��Ķ���ɱ��" + name() + HIG "֮��"]), 100);          
                                        }
                                        else
                                        {                  
                                                if (environment(tob) == environment(dob))                                  
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "��Ķ���ɱ��" + name() + HIG "֮��"]), 100);  
                                        }
                                }
                        }
                }
                else
                {
                        if( MEMBER_D->is_valib_member(query("id", dob)) )
                        {
                                GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,                                           
                                           "pot"      : pot + pot * 3 / 10,                                       
                                           "weiwang"  : weiwang + weiwang * 3 / 10,                               
                                           "score"    : score + score * 3 / 10,  
                                           "mar"      : mar + mar * 3 / 10,                           
                                           "prompt"   : "����սʤ" + name() + HIG "֮��"]), 100);                                    
                        }                                                                                          

                        else
                        {
                                GIFT_D->delay_bonus(dob,                                              
                                        ([ "exp"      : exp,                                           
                                           "pot"      : pot,                                       
                                           "weiwang"  : weiwang,                               
                                           "score"    : score,  
                                           "mar"      : mar,                           
                                           "prompt"   : "����սʤ" + name() + HIG "֮��"]), 100); 
                       }     
                }                                                                                                                                                                                                                                                 
        }

        // 100%����Ʒ
        if (1)
        {
                /*
                key_s_gift = keys(oblist);

                // 100%���ٱ�һ��
                if (1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob);
                                set("who_get/time", time()+30, gift_ob);//30���ڶ����ܼ�ȡ
                                gift_ob->move(environment(this_object()));                                                                           
                        }
                        else // ��¼֮
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
                
                // 30%������׷��һ����Ʒ
                if (random(10) < 3)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob2 = new(s_gift);
                        if (objectp(gift_ob2))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob2->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob2);
                                set("who_get/time", time()+10, gift_ob2);//30���ڶ����ܼ�ȡ
                                gift_ob2->move(environment(this_object()));                                                                           
                        }
                        else // ��¼֮
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }                       
                }
                // 10%������׷��һ��
                if (random(10) == 1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob3 = new(s_gift);
                        if (objectp(gift_ob3))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob3->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                //gift_ob3->set("who_get/id", "NONE");
                                //gift_ob3->set("who_get/time", time() + 30); // 30���ڶ����ܼ�ȡ
                                gift_ob3->move(environment(this_object()));                                                                           
                        }
                        else // ��¼֮
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
*/
                // 40%�ļ��ʵ�����
                if (random(100) < 40) 
                {
                        ran = random(100);

                        if (random(10) == 1)// 10%��������
                        {
                                gift_ob = new("/clone/armor/dongfang/chanyi");
                                
                                if (objectp(gift_ob))
                                {
                                        message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob);
                                        set("who_get/time", time()+30, gift_ob);//30���ڶ����ܼ�ȡ
                                        gift_ob->move(environment(this_object()));                                                                           
                                }
                        }
                        
                        if (random(100) < 3)// ����ָ�� 3%
                        {
                                gift_ob2 = new("/clone/armor/dongfang/heiyu");
                                
                                if (objectp(gift_ob2))
                                {
                                        message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob2->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob2);
                                        set("who_get/time", time()+30, gift_ob2);//30���ڶ����ܼ�ȡ
                                        gift_ob2->move(environment(this_object()));                                                                           
                                }
                        }                       

                        if (random(100) < 3)// ��Ѫ��
                        {
                                gift_ob3 = new("/clone/armor/dongfang/zixue");
                                
                                if (objectp(gift_ob3))
                                {
                                        message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob3->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob3);
                                        set("who_get/time", time()+30, gift_ob3);//30���ڶ����ܼ�ȡ
                                        gift_ob3->move(environment(this_object()));                                                                           
                                }
                        }

                        if (random(100) < 5)// ��Ӱ�������������� 5% ���һ��
                        {
                                switch(random(3))
                                {
                                        case 0:
                                                gift_ob4 = new("/clone/book/meiying-jian1");
                                        break;
                                        
                                        case 1:
                                                gift_ob4 = new("/clone/book/meiying-jian2");
                                        break;
                                        
                                        default:
                                                gift_ob4 = new("/clone/book/tianqing-miqi");
                                        break;
                                }

                                if (objectp(gift_ob4))
                                {
                                        message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob4->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob4);
                                        set("who_get/time", time()+30, gift_ob4);//30���ڶ����ܼ�ȡ
                                        gift_ob4->move(environment(this_object()));                                                                           
                                }
                        }
                }
        }
        
        // 5/100���ʵ�������ͭ��
        if (random(100) < (5+5*query_temp("apply/magic_find", dob)/100))
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren"+(1+random(2)));                     
                message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time()+30, ob_tongren);//30���ڶ����ܼ�ȡ
                ob_tongren->move(environment(this_object()));
        }
                
        // ��������Ʒ��ͳһ����giftd�ӿ�
        GIFT_D->fuben_boss_gift(this_object()); 
                                
/*
        // 20%���ʵ���������Ʒ
        // ͬʱ��50%���ʵ���2��
        if (random(10) < 2)
        {       
                gift_huoyan = new(huoyan);
                set("who_get/id", "NONE", gift_huoyan);
                set("who_get/time", time()+30, gift_huoyan);//30���ڶ����ܼ�ȡ
                gift_huoyan->move(environment(this_object()));  
                message_vision(HIW "��~~һ������$N" HIW "���ϵ���" + gift_huoyan->name() + 
                               HIW "�����ڵ��ϡ�\n" NOR, this_object());

                //log_file("qilin_gift", "�������� " + ctime(time()) + " ��������֮�䡣\n");
        }
*/
        // �������
        check_life();

        return ;
}  
