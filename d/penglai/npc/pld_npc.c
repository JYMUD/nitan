// nanhai.c

#include <ansi.h>

#define MAX_POINT     100000
#define MEMBER_D      "/adm/daemons/memberd" 

inherit NPC;

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
        return 1;
}

void unconcious()
{
/*
            // ��ֱֹ��call_die()
                if (query("qi") > 100000 && query("no_call_die"))
                {
                        revive();
                        return;
                }
*/
        die(query_last_damage_from());
}

void init()
{
        this_player()->set("env/combatd", 4);
}

void die(object killer)
{
        object dob;             // �������NPC����
        int n;                  // ���Խ������˵���Ŀ
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
        int exp2, pot2;
        object *t;              // ɱ���ҵ��˵Ķ����б�
        object tob;
        int i;
        object *inv;
        
        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        // ���影����Ʒ�б�
        mixed oblist;
                
        object env;

        oblist = query("oblist");


        if (! GIFT_D->is_open_pld())
        {
                destruct(this_object());
                return;
        } 
/*
            // ��ֱֹ��call_die()
                if (query("qi") > 100000)
                {
                        revive();
                        return;
                }
*/

        // ֪ͨ��ǰ���䣬�Ա����ˢ��
        env = environment(this_object());
        env->npc_die(this_object());
        
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
                exp = query("gift/exp");
                pot = query("gift/pot");
                       
                n = 0;
                n = sizeof(t);
        /*
                if (n > 1)
                {
                        exp /= n;
                        pot /= n;
                }
*/
                if (n > 1)
                {
                        exp /= 2;
                        pot /= 2;
                }        

                if (n)
                {                                
                        foreach(tob in t)
                        {
                                if (! objectp(tob))continue;
                                                
                                exp2 = exp;
                                pot2 = pot;                
                                /*                       
                                // ���ն��ѫ������10%
                                if (tob->query_temp("apply/zhanyao"))
                                {
                                               exp2 = exp2 + exp2 / 10;
                                               pot2 = pot2 + pot2 / 10;
                                }
                                */
                                if (objectp(tob) && living(tob))
                                {
                                        if (environment(tob) == environment(dob))
                                                GIFT_D->delay_bonus(tob,
                                                        ([ "exp"      : exp2 + ((tob == dob) ? exp2 / 10 : 0),
                                                              "pot"      : pot2 + ((tob == dob) ? pot2 / 10 : 0),
                                                              "prompt"   : "��Ķ�����" + name() + "֮��"]));
                                }
                        }
                }
                else
                {        /*                       
                        // ���ն��ѫ������10%
                        if (dob->query_temp("apply/zhanyao"))
                        {
                                exp = exp + exp / 10;
                                pot = pot + pot / 10;
                        }
                        */
                        GIFT_D->delay_bonus(dob,
                                ([ "exp"      : exp,
                                   "pot"      : pot,
                                   "prompt"   : "���ڴ��" + name() + "֮��"]));
                }
        }

        // һ�����ʵ���Ʒ��ɱ�ҵ�������dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // �жϼ���
                if ((MEMBER_D->is_valib_member(dob->query("id")) || random(4) == 1) 
                        && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                {
                        // �����Ʒ--������Ʒ
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIR "��~~һ������$N" HIR "���ϵ���һ��������\n" NOR, this_object(), dob);
                                gift_ob->set("who_get/id", dob->query("id"));
                                gift_ob->set("who_get/time", time() + 60); // һ������ֻ���Լ���ȡ
                                gift_ob->move(environment(this_object()));
                        }
                        else // ��¼֮ 
                        {
                                        log_file("killed-gift-none", s_gift + "\n");
                        }
                }
        }

        // ������Ǯ��������Ʒ
        if (1)
        {
                inv = all_inventory(this_object());
                inv -= ({ 0 });
                   i = sizeof(inv);
                while (i--)
                    {
                        if (objectp(dob))
                        {
                            inv[i]->set("who_get/id", dob->query("id"));
                           inv[i]->set("who_get/time", time() + 60);
                        }
                         inv[i]->move(environment(this_object()));
                }
        }

        destruct(this_object());

        return;
}
