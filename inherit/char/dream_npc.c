// dream_npc.c

#include <ansi.h>

#define MAX_POINT     180000

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

void fight_ob(object ob)
{
        if( is_fighting() || !query("end_time") )
                return ::fight_ob(ob);

        set_temp("end_time", time() + query("end_time"));
        return ::fight_ob(ob);
}

varargs void unconcious(object defeater)
{
        object ob;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/
        die(defeater);
        return;
}

void init()
{
        // ����������
        if( userp(this_player()) && random(4) == 1 && !query_temp("apply/invisible", this_player()) )
        {
                kill_ob(this_player());
        }

        set("env/combatd", 4, this_player());
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
        int i, mar;
        object *inv, objenv;

        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        // ���影����Ʒ�б�
        mixed oblist;

        object env;
        object ob;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/

        if( time() < query_temp("end_time", this_object()) ) // ʱ��û�е�����������
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "ȫ����һ����⣬�漣��Ļ���������\n\n" NOR, this_object());
                return;
        }
        
        oblist = query("oblist");

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

        // ������ͼ
        // ���22-30
        if( query("quest_tuteng/start", dob) )
        {
                int n_tt;
                object ob_tt;

                if (random(10000) == 1)
                {
                        n_tt = 22 + random(14);
                        if (n_tt == 28 && random(10) > 1)n_tt = 25;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "������һ�ŵ�����ͼ��Ƭ��\n" NOR);
                                ob_tt->move(dob, 1);
                        }
                }
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");

                n = 0;
                n = sizeof(t);


                if (n > 1)
                {
                        exp /= n;
                        pot /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (! objectp(tob))continue;

                                exp2 = exp;
                                pot2 = pot;

                                // ���ն��ѫ������10%
                                if( query_temp("apply/zhanyao", tob) )
                                {
                                        exp2 = exp2 + exp2 / 10;
                                        pot2 = pot2 + pot2 / 10;
                                }
                                // ���ʮ�������ѫ������5%
                                if( query_temp("apply/year10", tob) )
                                {
                                        exp2 = exp2 + exp2 / 20;
                                        pot2 = pot2 + pot2 / 20;
                                }

                                if (objectp(tob) && living(tob))
                                {
                                        if (environment(tob) == environment(dob))
                                                GIFT_D->event_bonus(tob,
                                                        ([ "exp"      : exp2 + ((tob == dob) ? exp2 / 10 : 0),
                                                           "pot"      : pot2 + ((tob == dob) ? pot2 / 10 : 0),
                                                           "prompt"   : "��Ķ���ɱ��" + name() + "֮��"]));
                                }
                        }
                }
                else
                {
                        // ���ն��ѫ������10%
                        if( query_temp("apply/zhanyao", dob) )
                        {
                                exp = exp + exp / 10;
                                pot = pot + pot / 10;
                        }
                        // ���ʮ�������ѫ������5%
                        if( query_temp("apply/year10", dob) )
                        {
                                exp = exp + exp / 20;
                                pot = pot + pot / 20;
                        }

                        GIFT_D->event_bonus(dob,
                                ([ "exp"      : exp,
                                   "pot"      : pot,
                                   "prompt"   : "����ɱ��" + name() + "֮��"]));
                }
        }

        // һ�����ʵ���Ʒ��ɱ�ҵ�������dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // �жϼ���
                if( random(10) == 1
                        && random(MAX_POINT / ITEM_D->gift_point()) < gift_point )
                {
                        // �����Ʒ--������Ʒ
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIR "��~~һ������$N" HIR "���ϵ���һ��������\n" NOR, this_object(), dob);
                                set("who_get/id", query("id", dob), gift_ob);
                                set("who_get/time", time()+60, gift_ob);//һ������ֻ���Լ���ȡ
                                gift_ob->move(environment(this_object()));
                        }
                }
        }

        // ������Ǯ��������Ʒ
        if (random(5) == 1)
        {
                inv = all_inventory(this_object());
                inv -= ({ 0 });
                i = sizeof(inv);
                while (i--)
                {
                        if (objectp(dob))
                        {
                                set("who_get/id", query("id", dob), inv[i]);
                                set("who_get/time", time()+60, inv[i]);
                        }
                        inv[i]->move(environment(this_object()));
                }
        }

        // 1/550000���ʵ�������ͭ��
        if (random(550000) == 1 && objectp(dob))
        {
                object ob_tongren;

                if( random(2) )
                        ob_tongren = new("/clone/tongren/tongren1");
                else
                        ob_tongren = new("/clone/tongren/tongren2");
                ob_tongren->move(dob, 1);
                write(HIR "��õ�һ��" + ob_tongren->name() + HIR "��\n");
        }

        //1/5000���ʵ��������ɹ�
        if (random(5000) == 1 && objectp(dob))
        {
                object ob_xianguo;

                ob_xianguo = new("/clone/fam/item/penglai-xianguo");
                ob_xianguo->move(dob, 1);
                write(HIR "��õ�һ��" + ob_xianguo->name() + HIR "��\n");
        }

        // �ھ�ͷ�����ɱ����ͷ�߿ɻ�ȡ�������
        objenv = environment(this_object());
        if( objectp(objenv) && query("short", objenv) == "��ͷ�����" )
        {
                mar = 25;
                if( query("experience", dob) >= 2000000000) mar=0;
                if( query("experience", dob)-query("learned_experience", dob) >= 10000000) mar=0;
                addn("experience", mar, dob);
        }

        destruct(this_object());

        return;
}
