// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIW "劍冢刀客" NOR, ({ "jianzhong daoke", "jianzhong", "daoke" }) );
        set("title", HIY "「隱士」" NOR);
        set("gender", "男性");
        set("age", 38);
        set("long", @LONG
這是一名中年男子，一副刀客裝扮，身上透射出陣陣殺氣，看上去不好對付。
LONG );
        set("combat_exp", 3000000);
        set("shen_type", 0);
        set("max_neili", 9000);
        set("neili", 9000);
        set("max_jing", 12000);
        set("jing", 12000);
        set("max_qi", 300000);
        set("eff_qi", 300000);
        set("qi", 300000);
        set("jingli", 12000);
        set("max_jingli", 12000);
        set("level", 20);

        set("no_clean_up", 1);

        //set("no_nuoyi", 1); // 不被挪移影響

        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set_skill("martial-cognize", 200);
        set_skill("unarmed", 180);
        set_skill("sword", 180);
        set_skill("blade", 180);
        set_skill("parry", 180);
        set_skill("dodge", 180);
        set_skill("force", 180);
        set_skill("cuff", 180);

        set_skill("wudang-xinfa", 180);
        set_skill("huashan-sword", 180);
        set_skill("luohan-quan", 180);
        set_skill("shaolin-shenfa", 180);
        set_skill("chuangwang-dao", 180);


        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "chuangwang-dao");
        map_skill("force", "shaolin-xinfa");

        prepare_skill("cuff", "huashan-quan");

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.xiangmo" :),
                (: perform_action, "blade.xiong" :),
                (: exert_function, "recover" :)
        }) );

        set("jiali", 30);

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 3000,
                "mar"   : 150,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM10"    :       100,   // 低級普通裝備
                "RA&RANDOM20"    :       40,    // 低級普通裝備
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/yin-erhuan"    :       30,
                "FI&/clone/armor/biyu-chai"     :       20,
                "FI&/clone/tessera/rune03"  :   1,
        ]));
        setup();

        carry_object("/clone/weapon/blade")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        set_temp("born_time", time());
        if (clonep()) keep_heart_beat();

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
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 200 + random(100), ob);
        return HIY "$N" HIY "大喝一聲，拚死反抗，竟逼得$n" HIY "手忙腳亂。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("mess", "聽說" + 
                        env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")一帶出現的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        if (random(2) == 1)
        {
                command("chat* sigh");
                command("chat 想不到我隱居此處竟也被仇家找到，天亡我也！");
                CHANNEL_D->channel_broadcast("rumor", "聽說" + name() + HIM "被江湖人士所殺。" NOR);
        }
        else
        {
                message_vision(HIG "猛然間，劍光一閃，跳出一個蒙面黑衣人將$N " HIG " 抱起，殺出一條血路，逃命去了 ...\n" NOR,
                               this_object());
                command("chat 哼，區區鼠輩，竟也想取吾命！");
                CHANNEL_D->channel_broadcast("rumor", "聽說" + name() + HIM "遭江湖人士追殺，被"
                                      "神秘黑衣人救走後從此銷聲匿跡。" NOR);
        }
}
