// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();

void create()
{
        set_name(HIY "��ʬ����" NOR, ({ "jiangshi daozhang", "jiangshi", "daozhang" }));
        set("title", HIR "" NOR);
        set("gender", "����");
        set("age", 32);
        set("long", @LONG
��˵��ԭ��ʬ���У��շ���ʬҲ�����һ��ְҵ�����ڳ���
����ʬ�򽻵������ֵ�ʿ�ڱ���ʬҧ�˺�Ҳʧȥ�����ǣ���
Ϊ���˰�ʬ�����зǳ����ɱ���ԡ���Щ��ʿҲ�ͱ����ǳ�
֮Ϊ��ʬ��������ԭ��ʬ����������Ѿ�������ɱ��������
�������߲��Թ��ڡ�
LONG);
        set("attitude", "friendly");
        set("str", 80);
        set("int", 80);
        set("con", 80);
        set("dex", 80);
        set("per", 1);
        set("shen_type", 0);

        set("qi", 1500000000);
        set("max_qi", 1500000000);

        set("jing", 92000000);
        set("max_jing", 92000000);
        set("jingli", 92000000);
        set("max_jingli", 92000000);

        set("neili", 400000);
        set("max_neili", 400000);
        set("jiali", 4000);
        set("combat_exp", 2000000000);
        set("level", 100);

        //set("reborn/times", 1);
        set("special_skill/guimai", 1);

        set_skill("force", 2000);
        set_skill("pixie-jian", 2000);
        set_skill("surge-force", 2000);
        set_skill("six-finger", 2000);
        set_skill("sword", 2000);
        set_skill("finger", 2000);
        set_skill("whip", 2000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("unarmed", 2000);
        set_skill("strike", 2000);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 2000);
        set_skill("throwing", 2000);
        set_skill("taishang-wangqing", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 2000);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "six-finger");

        prepare_skill("finger", "six-finger");

        set_temp("apply/attack",100000);
        set_temp("apply/defense", 60000);
        set_temp("apply/damage", 30000);
        set_temp("apply/unarmed_damage", 40000);
        set_temp("apply/armor", 60000);
        set_temp("apply/fy", 10);
        set_temp("apply/qy", 10);

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.duo and sword.gui") :),
                (: command("perform sword.pi and sword.po") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.jian twice" :),
                (: perform_action, "finger.tian twice" :),
        }) );

        set("end_time", 300);
        set("death_msg", RED"\n$N������һ̲Ѫˮ��\n\n"NOR);

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 3000,
                "mar"   : 150,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM50"    :       100,   // �ͼ���ͨװ��
                "RA&RANDOM60"    :       40,    // �ͼ���ͨװ��
                "FI&/clone/misc/boss_item/tianshi-guifu":         20,
                "FI&/clone/armor/tianshi-xiang"         :         20,
                "FI&/clone/tessera/rune11"  :   1,
                "FI&/clone/armor/huangfu-zhi"           :         20,
                "FI&/clone/tongren/tongren"+(1+random(2)):        5,
        ]));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
        set_temp("born_time", time());
        //if (clonep()) keep_heart_beat();
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
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int wound;

        if (random(5) == 1)ob->start_busy(8 + random(16));
        wound = 20000 + random(20000) - me->query_temp("apply/armor");
        if (wound < 1)wound = 1;
        me->receive_wound("qi", wound, ob);
        return HIY "$N" HIY "ŭ��һ�����������������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        return ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N����ææ�����ˡ�\n", this_object());

                CHANNEL_D->channel_broadcast("mess", env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")һ�����ֵ�" +
                        HIR + this_object()->short() + HIG "��ʧ�ˡ�\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

varargs void die(object killer)
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( time() < query_temp("end_time") ) // ʱ��û�е�����������
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "���һ���������ط�����Ѫ����������\n\n" NOR, this_object());
                return;
        }

        if (! objectp(killer))
                killer = query_last_damage_from();

        if( objectp(killer) && query("family/family_name", killer) == "�䵱��")
                set("rewards/gongxian", 300);

        return ::die(killer);
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}
