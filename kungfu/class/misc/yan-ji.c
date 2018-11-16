// This program is a part of NT MudLIB
// yanji.c

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name("�ֻ�", ({ "yan ji", "yan" }));
        set("title", HIG "����ҽ��" NOR);
        set("gender", "����");
        set("long", "����һ��û�佭��ҽ����\n");
        set("age", 45);
        set("fight_boss", 1);
        set("combat_exp", 12000000);
        set("level", 10);
        set("attitude", "peaceful");
        set("shen", 0);
        set("level", 30);

        set("str", 41);
        set("int", 42);
        set("con", 44);
        set("dex", 40);

        set("qi", 1000000);
        set("max_qi", 1000000);
        set("jing", 500000);
        set("max_jing", 500000);
        set("jiali", 1000);

        set_skill("unarmed", 260);
        set_skill("dodge", 260);
        set_skill("parry", 260);
        set_skill("blade", 260);
        set_skill("wudang-quan", 260);
        set_skill("hujia-daofa", 260);
        map_skill("unarmed", "wudang-quan");
        map_skill("blade", "hujia-daofa");

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        //set("clear_fuben", 1);
        set("auto_perform", 1);
        set("rewards", ([
                "exp"   : 200000,
                "pot"   : 60000,
                "mar"   : 1500,
                "score" : 300,
                "gold"  : 50,
        ]));

        set("drops", ([
                "RA&RANDOM10"    :       100,   // �ͼ���ͨװ��
                "RA&RANDOM20"    :       40,    // �ͼ���ͨװ��
                "FI&/clone/goods/enchant-scroll"   :   20,
                "FI&/clone/goods/sun"   :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 1,
        ]));

        set_temp("apply/attack", 500);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/damage", 500);
        set_temp("apply/armor", 500);
        set_temp("apply/reduce_damage", 70);
        set_temp("apply/reduce_busy", 3);
        set_temp("apply/add_busy", 2);
        setup();

        add_money("silver", 20);
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
        set_temp("born_time", time());
        if (clonep()) keep_heart_beat();
}

/*
void init()
{
        object me;

        ::init();
        if (interactive(me = this_player()) && !is_fighting())
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }
}
*/

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
                        HIR + this_object()->short() + HIG "��ʧ�ˡ�\n" NOR, users());

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat ������ѧ���������ҵ��������������˾Ͳ������ˣ��Һް��� ...");
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + name() + HIM "��������ʿ��ɱ��" NOR);
}

void die(object killer)
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

        if( objectp(killer) && query("family/family_name", killer) == "�������")
                set("rewards/gongxian", 300);

        return ::die();
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
