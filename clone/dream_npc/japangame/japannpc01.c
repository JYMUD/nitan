inherit NPC;
#define MAX_POINT     100000
#define MEMBER_D      "/adm/daemons/memberd"
#define DB_D          "/adm/daemons/dbd"

#include <ansi.h>


void create()
{
        set_name(HIR "����" NOR, ({ "wo kou", "wo", "kou" }));

        set("age", 20);
        set("str", 30);
        set("dex", 10);
        set("max_qi", 10000);
        set("max_ging", 10000);
                set("eff_jing", 10000);
                set("max_jing", 10000);
                set("max_neili", 25000);
                set("neili", 25000);
                set("jingli", 10000);
                set("max_jingli", 10000);
                set("jingli", 10000);
                set("eff_jingli", 10000);
        set("combat_exp", 500000);


        set_temp("apply/parry", 50);
        set_temp("apply/dodge", 50);
                set_temp("apply/dex", 10);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 10);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 10);

                set_skill("dodge", 50);
                set_skill("unarmed", 50);

                set("gift/exp", 500);
                set("gift/pot", 160);
                set("oblist", ([
                        "/clone/monely/gold" : 5,
                ]));
        setup();
                add_money("silver", 4 + random(6));
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
        // ����������
        if( userp(this_player()) && random(4) == 1 && !query_temp("apply/invisible", this_player()) )
        {
                kill_ob(this_player());
        }
}

void die(object killer)
{
        object dob;             // �������NPC����
        int n;                  // ���Խ������˵���Ŀ
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
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

                                if (n > 1)
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
                                                                   GIFT_D->event_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "��Ķ���ɱ��" + name() + "֮��"]));

                                                 }
                                        }
                                }
                                else
                                {
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
                        if( (MEMBER_D->is_valid_member(query("id", dob)) || random(4) == 1 )
                                && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                        {
                                // �����Ʒ--������Ʒ
                                gift_ob = new(s_gift);
                                if (objectp(gift_ob))
                                {
                                        message_vision(HIR "��~~һ������$N" HIR "���ϵ���һ��������\n" NOR, this_object(), dob);
                                        set("who_get/id",query("id",  dob), gift_ob);
                                        set("who_get/time", time()+60, gift_ob);//һ������ֻ���Լ���ȡ
                                        gift_ob->move(environment(this_object()));
                                }
                                else // ��¼֮ 
                                {
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
                                            set("who_get/id",query("id",  dob), inv[i]);
                                           set("who_get/time", time()+60, inv[i]);
                                  }
                  inv[i]->move(environment(this_object()));
                        }
                }

                // ��¼
                if (objectp(dob))
                {
                        DB_D->set_data("japangame/"+query("id", dob),
                                           DB_D->query_data("japangame/"+query("id", dob))+1);

                        tell_object(dob, HIG "��ϲ�������ۻ�ɱ����������Ϊ " + 
                                        DB_D->query_data("japangame/"+query("id", dob))+"��\n"NOR);
                        
                }
                destruct(this_object());

        return;
}
