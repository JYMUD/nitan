inherit NPC;

#include <ansi.h>

void create()
{
        set_name(HIR "������" NOR, ({ "wang tianya", "wang", "tianya", "rcwiz"}));
        set("title", HIY "��ת�ػ�����" NOR);
        set("gender", "����");
        set("age", 28);
        set("long", @LONG
�������˶�ת�ؿ��ػ����񣬻���������Դ�ͨ��ת֮���ˣ����Ͱɣ�
LONG);
        set("attitude", "friendly");
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("per", 30);
        set("shen_type", 0);

        set("no_nuoyi", 1); // ����Ų��Ӱ��
        
        set("qi", 200000000);
        set("max_qi", 200000000);

        set("jing", 400000000);
        set("max_jing", 400000000);
        set("jingli", 400000000); 
        set("max_jingli", 400000000); 

        set("neili", 100000); 
        set("max_neili", 100000); 
        set("jiali", 4000); 
        set("combat_exp", 1000000000);

        set("scborn/ok", 1);
        set("special_skill/guimai", 1);
        
        set_skill("force", 1400);
        set_skill("pixie-jian", 1400);
        set_skill("surge-force", 1400);
        set_skill("liumai-shenjian", 1400);
        set_skill("sword", 1400);
        set_skill("finger", 1400);
        set_skill("whip", 1400);
        set_skill("dodge", 1400);
        set_skill("parry", 1400);
        set_skill("unarmed", 1400);
        set_skill("strike", 1400);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1400);
        set_skill("throwing", 1400);
        set_skill("jueqing-quyu", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 1400);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",20000);
        set_temp("apply/defense", 20000);
        set_temp("apply/damage", 14000);
        set_temp("apply/unarmed_damage", 14000);
        set_temp("apply/armor", 30000);
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

        carry_object("/clone/weapon/zhantian-zhiren")->wield();
        carry_object("/clone/cloth/huancai-yi")->wear();
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
        me->receive_wound("qi", 8500 + random(5600), ob);
        return HIY "$N" HIY "΢΢һЦ��������ת�����Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(100) == 1)                                                
                set("neili", query("max_neili"));

        return ::heart_beat();
}

void unconcious()
{
        // ��ֱֹ��call_die()
        if (query("qi") > 600000)
        {
                revive();
                return;
        }
        die(query_last_damage_from());
}

void die(object killer)
{
        object myroom;
        
        // ��ֱֹ��call_die()
        if (query("qi") > 600000)
        {
                revive();
                return;
        }

        myroom = this_object()->query("myroom");
        myroom->set("exits", ([ "up" : "/kungfu/class/sky/sky2zhuan" ]));
        
        message_vision(HIR "һ���â������ͨ��������Դ֮���Ѿ�������\n" NOR, this_object());
        destruct(this_object());

        return;
}

