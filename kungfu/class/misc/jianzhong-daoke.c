// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIW "��ڣ����" NOR, ({ "jianzhong daoke", "jianzhong", "daoke" }) );
        set("title", HIY "����ʿ��" NOR);
        set("gender", "����");
        set("age", 38);
        set("long", @LONG
����һ���������ӣ�һ������װ�磬����͸�������ɱ��������ȥ���öԸ���
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

        //set("no_nuoyi", 1); // ����Ų��Ӱ��

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
                "RA&RANDOM10"    :       100,   // �ͼ���ͨװ��
                "RA&RANDOM20"    :       40,    // �ͼ���ͨװ��
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
        return HIY "$N" HIY "���һ����ƴ�����������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
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
                message_vision("$N����ææ�����ˡ�\n", this_object());

                CHANNEL_D->channel_broadcast("mess", "��˵" + 
                        env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")һ�����ֵ�" +
                        HIR + this_object()->short() + HIG "��ʧ�ˡ�\n" NOR);

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
                command("chat �벻�������Ӵ˴���Ҳ������ҵ���������Ҳ��");
                CHANNEL_D->channel_broadcast("rumor", "��˵" + name() + HIM "��������ʿ��ɱ��" NOR);
        }
        else
        {
                message_vision(HIG "��Ȼ�䣬����һ��������һ����������˽�$N " HIG " ����ɱ��һ��Ѫ·������ȥ�� ...\n" NOR,
                               this_object());
                command("chat �ߣ������󱲣���Ҳ��ȡ������");
                CHANNEL_D->channel_broadcast("rumor", "��˵" + name() + HIM "�⽭����ʿ׷ɱ����"
                                      "���غ����˾��ߺ�Ӵ������伣��" NOR);
        }
}
