// This program is a part of NT MudLIB
// yangkang.c �

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name("�", ({"yang kang", "yang"}));
        set("gender", "����");
        set("title", HIY "С��ү" NOR);
        set("age", 26);
        set("class", "taoist");
        set("long",
                "�����Ǵ��ɵ�С��ү���ʵ����ҽ�����������֮�ӡ�\n"
                "����ò��������ü����ƺ�������һ˿�ƻ�����ɫ��\n");
        set("attitude", "friendly");
        set("shen", 0);
        set("str", 25);
        set("int", 26);
        set("con", 26);
        set("dex", 25);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 30000000);
        set("max_neili", 3000000);
        set("jiali", 2000);

        set("combat_exp", 120000000);
        set("level", 30);
        set("fight_boss", 1);

        set_skill("force", 400);
        set_skill("quanzhen-xinfa", 400);
        set_skill("sword", 400);
        set_skill("quanzhen-jian", 400);
        set_skill("dodge", 400);
        set_skill("jinyan-gong", 400);
        set_skill("parry", 400);
        set_skill("unarmed", 400);
        set_skill("finger", 400);
        set_skill("zhongnan-zhi", 400);
        set_skill("literate", 400);
        set_skill("taoism", 400);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        prepare_skill("finger", "zhongnan-zhi");

        create_family("ȫ���", 3, "����");

        set_temp("apply/attack", 400);
        set_temp("apply/defense", 400);
        set_temp("apply/damage", 500);
        set_temp("apply/armor", 500);
        set_temp("apply/reduce_damage", 30);
        set_temp("apply/reduce_busy", 10);
        set_temp("apply/add_busy", 3);

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("clear_fuben", 1);
        set("auto_perform", 1);
        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 200000,
                "pot"   : 60000,
                "mar"   : 1500,
                "score" : 300,
                "gold"  : 50,
        ]));
        set("drops", ([
                "RA&RANDOM30"    :       100,   // �ͼ���ͨװ��
                "RA&RANDOM40"    :       40,    // �ͼ���ͨװ��
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"   :   20,
                "FI&/clone/goods/moon"  :   20,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 1,
        ]));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/kungfu/class/quanzhen/obj/greyrobe")->wear();
        set_temp("born_time", time());
        if (clonep()) keep_heart_beat();
}

int accept_fight(object ob)
{
        command("say �ҿ�û��Ȥ�����棬����ҹ�����");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIW "$N" HIW "��ɫһ�䣬����һ��ɱ����ŭ"
                       "�ȵ�����һ��" + RANK_D->query_rude(ob) +
                       "�����ɣ�\n" NOR, this_object());
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if( !living(this_object()) )
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("���˾����Ժøߣ����������֡�\n");
}

int accept_touxi(object ob)
{
        return notify_fail("���˾����Ժøߣ����������֡�\n");
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(3 + random(6));
	me->receive_wound("qi", 100 + random(100), ob);
        return HIY "$N" HIY "���һ����ƴ�����������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(100) == 1)
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

                message("vision", HIG"��" HIR"����" HIG"��" HIW +
                        env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")һ�����ֵ�" +
                        HIR + this_object()->short() + HIR "��ʧ�ˡ�\n" NOR, users());

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat �����ǽ��С��ү����ɱ�ң�����˵�� ...");
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + name() + HIM "������������ˡ�" NOR);
}
