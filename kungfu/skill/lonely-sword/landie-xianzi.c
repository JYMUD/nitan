


#include <ansi.h>

inherit NPC;

string lookdesc = "��һ���嵭���£�����������ѩ���������֮�������䣬�������ӡ�\n";

void create()
{
        set_name(HIM "��������" NOR, ({ "landie xianzi", "landie", "xianzi"}));
        set("title", HIC "����ɾ�" NOR);
        set("gender", "Ů��");
        set("age", 22);
        set("long", lookdesc); // ��ʼ��ʱ����������lookdesc������ʾ�Ǹ�����ܹ���������˺�
        set("attitude", "friendly");
        set("str", 21);
        set("int", 40);
        set("con", 45);
        set("dex", 46);
        set("per", 30);
        set("shen_type", 1);
        set("scborn/ok", 1);
        set("no_nuoyi", 1); // ����Ų��Ӱ��
        set("qi", 5000000);
        set("max_qi", 5000000);

        set("jing", 2000000);
        set("max_jing", 2000000);
        set("jingli", 2000000); 
        set("max_jingli", 2000000); 

        set("neili", 30000); 
        set("max_neili", 30000); 
        set("jiali", 600); 
        set("combat_exp", 8000000);

        set_skill("force", 400);
        set_skill("suxin-jue", 400);
        set_skill("yunv-xinjing", 400);
        set_skill("sword", 400);
        set_skill("yunv-jian", 400);
        set_skill("suxin-jian", 400);
        set_skill("quanzhen-jian", 400);
        set_skill("whip", 400);
        set_skill("yinsuo-jinling", 400);
        set_skill("dodge", 400);
        set_skill("yunv-shenfa", 400);
        set_skill("parry", 400);
        set_skill("unarmed", 400);
        set_skill("meinv-quan", 400);
        set_skill("strike", 400);
        set_skill("tianluo-diwang", 400);
        set_skill("zuoyou-hubo", 400);
        set_skill("literate", 400);
        set_skill("throwing", 400);
        set_skill("yufeng-zhen", 400);
        set_skill("martial-cognize", 600);

        map_skill("force", "yunv-xinjing");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "suxin-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        set_temp("apply/attack", 1500);
        set_temp("apply/defense", 1500);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.wang and unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "whip.feng twice" :),
        }) );

        set("jianling-summon",1); // ���ᱻ����DAMAGE_ALL�˺�
        
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
}

// ��ʼ��
void init_me(object jianling, object wanjia)
{
        set("jianling", jianling);
        set("mytarget", wanjia);
        set("env", environment(jianling));
        
        set("long", lookdesc + HIR "Ŀǰֻ��" + HIY + wanjia->name() +  HIR "�ܹ���������˺���\n");
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
        ob->start_busy(12 + random(12));
        me->receive_wound("qi", 200000 + random(90000), ob);
        return HIY "$N" HIY "����һ�����������������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}


int receive_damage(string type, int damage, object who)
{
        // ֻ��ָ��Ŀ����ܶ�������˺�
        if (! who)return 0;
        
        if ( who != query("mytarget"))
        {
                message_vision(HIG "$N" HIG "��͸��$n" HIG "�Ĺ��ƣ���˿�����ˣ�\n" NOR, this_object(), who);
                return 0;
        }
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)                                              
                set("neili", query("max_neili"));

        if (environment(this_object()) != query("env"))
        {
                if (objectp(query("env")))this_object()->move(query("env"));
        }
        
        return ::heart_beat();
}

void unconcious()
{
        // ��ֱֹ��call_die()
        if (query("qi") > 60000)
        {
                revive();
                return;
        }
        die(query_last_damage_from());
}

void die(object killer)
{

        message_vision(HIC "ֻ��һ����â��$N" HIC "��������$N" HIC "������һ�����������ˣ�\n" NOR, this_object());
                                        
        command("chat* tlbb " + query("id"));                           
        destruct(this_object());
        
        return;
}

void remove()
{
        object dob;
        
        dob = query("jianling");// ��ȡ��Ӧ�Ľ���OB
        
        if (! objectp(dob))return;
        
        delete("mylandie", dob);//֪ͨ���飬������ʧ��
        set("last_summon_landie", time(), dob);//֪ͨ���飬������ʧʱ��
        
        return;
}
