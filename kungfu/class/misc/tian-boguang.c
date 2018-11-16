// This program is a part of NT MudLIB
// boguang.c �ﲮ��

#include <ansi.h>
#include <command.h>
inherit BOSS;

void death_msg();
void random_move();
int  checking(object me, object ob);
int  fast_attack(object me, object ob);
int  is_stay_in_room()  { return 1; }

void create()
{
        set_name("�ﲮ��", ({ "tian boguang", "tian", "boguang" }));
        set("nickname", HIM "�������" NOR);
        set("long", "�ﲮ��Ϊ�����г������õĲɻ�����һ�ֿ쵶������������˫���Ṧ��������Ҳ��һ�ȵġ�\n");
        set("gender", "����");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 38);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);

        set("max_qi", 2000000);
        set("max_jing", 1000000);
        set("neili", 2000000);
        set("max_neili", 2000000);
        set("jiali", 1500);
        set("no_suck", 1);
        set("combat_exp", 30000000);
        set("level", 30);
        set("fight_level", 30);
        //set("fight_boss", 1);
        set("score", 5000);

        set_skill("unarmed", 300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("kuangfeng-blade", 300);
        set_skill("blade", 300);
        set_skill("unarmed", 300);
        set_skill("literate", 250);
        set_skill("ding-dodge", 300);
        set_skill("ding-force", 300);
        set_skill("martial-cognize", 400);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("parry", "kuangfeng-blade");
        map_skill("blade", "kuangfeng-blade");

        set_temp("apply/attack", 200);
        set_temp("apply/defense", 200);
        set_temp("apply/damage", 600);
        set_temp("apply/armor", 500);
        set_temp("apply/reduce_damage", 40);
        set_temp("apply/reduce_busy", 6);
        set_temp("apply/add_busy", 3);

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.kuang" :),
        }));

        set("clear_fuben", 1);
        //set("auto_perform", 1);
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
                "FI&/clone/book/kuangfeng-book"  :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/book/kuangfeng-dao1"  :   10,
                "FI&/clone/book/kuangfeng-dao2"  :   10,
                "FI&/clone/tessera/rune05"  :   1,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 1,
        ]));
        set("end_time", 300);
        set("death_msg", (: death_msg :));
        setup();
        set("startroom", "d/huashan/path1");
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
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

void kill_ob(object me)
{
        remove_call_out("checking");
        call_out("checking", 1, this_object(), me);
        return ::kill_ob(me);
}

int checking(object me, object ob)
{
        object weapon;

        if( !objectp(me) || !objectp(ob) )
                return 0;

        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        if( !query_temp("weapon", me) )
        {
                weapon = new("/clone/weapon/gangdao");
                weapon->move(me);
                weapon->wield();
        }

        if( me->is_fighting() )
        {
                if( !query_temp("attack_pending", me )
                 && objectp(weapon=query_temp("weapon", me)) )
                {
                        set_temp("attack_pending", 1, me);
                        remove_call_out("fast_attack");
                        call_out("fast_attack", 3, me, ob);
                }

                return 1;
        } else
        if( query("attack_pending", me) == 1 )
        {
                delete_temp("attack_pending", me);
                remove_call_out("fast_attack");
                return 1;
        }

        return 1;
}

int fast_attack(object me, object ob)
{
        int i, num;

        remove_call_out("fast_attack");
        delete_temp("attack_pending", me);
        num = random(3) + 5;

        message_vision("�ﲮ���һ����ʹ����쵶����������$N������" + chinese_number(num) + "����\n", ob);

        for (i = 1; i < num + 1; i++)
        {
                if( !me->is_fighting(ob) ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        }

        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 200 + random(100), ob);
        return HIY "$N" HIY "���һ����ƴ�����������Ƶ�$n" HIY "��æ���ҡ�\n" NOR;
}

void death_msg()
{
        command("chat* heng");
       	command("chat ��������ԩ��·խ����үү�һ����£��������� ����");
	CHANNEL_D->channel_broadcast("rumor", "��˵" + name() + HIM "��������"
			                     "ʿ׷ɱ����ȴ����ƴɱ��ͻ����Χ������������" NOR);
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
