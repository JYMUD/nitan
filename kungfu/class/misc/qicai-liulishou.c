// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIY "�߲�" HIM "������" NOR, ({ "qicai liulishou", "qicai", "liulishou" }) );
        set("title", HIW "ʥ��" HIR "����" NOR);
        set("gender", "����");
        set("age", 8888);
        set("long", @LONG
����һֻ�������ع��ޣ�ȫ��ó��߲�֮ɫ��ͷ����С��һ�Ի�Բ����
����˸�����˵Ĺ�â��
LONG );
        set("combat_exp", 2000000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 900000000);
        set("eff_qi", 900000000);
        set("qi", 900000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

        set("no_nuoyi", 1); // ����Ų��Ӱ��

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 300);

        set_skill("unarmed", 4000);
        set_skill("sword", 4000);
        set_skill("parry", 4000);
        set_skill("dodge", 4000);
        set_skill("force", 4000);

        set("jiali", 1000);

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 3000,
                "mar"   : 15,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM30"    :       100,   // �ͼ���ͨװ��
                "RA&RANDOM40"    :       40,    // �ͼ���ͨװ��
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/qicai-xue"      :   20,
        ]));

        set_temp("apply/attack", 150000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set_temp("born_time", time());
                //keep_heart_beat();
        }

        setup();
}

int accept_fight(object ob)
{
        message_vision("$Nһ���޺����˹�����\n",
                       this_object(), ob);
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

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(20 + random(10));
        me->receive_wound("qi", 5000 + random(3000), ob);
        return HIY "$N" HIY "��Χ�������ƣ�ֱ�Ƶ�$n" HIY "ͷ��Ŀѣ��\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N��Хһ��������һ�Ż��棬��ʧ����ʡ�\n", this_object());
                
                CHANNEL_D->channel_broadcast("mess", "��˵"+
                        env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")һ�����ֵ�" +
                        HIR + this_object()->short() + HIG "��ʧ�ˡ�\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat �������˶���֮��ʵ��������ûȤ��");
        message_vision("$N��Хһ��������һ�Ż��棬��ʧ����ʡ�\n", this_object());
        CHANNEL_D->channel_broadcast("rumor",
                        "��˵" + name() + HIM "��һȺ������ʿ��ܣ����˶��顣" NOR);
}
