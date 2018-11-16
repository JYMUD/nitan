// donghai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("������̫��", ({ "prince of dragon", "dragon", "san taizi" }) );
        set("title", HIG "����" NOR);
        set("gender", "����");
        set("age", 23);
        set("long", @LONG
����һ��������ȵ������ˣ�������棬����������
LONG );
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 20000);
        set("neili", 20000);
        set("max_jing", 20000);
        set("jing", 20000);
        set("max_qi", 25000);
        set("qi", 25000);
        set("jingli", 20000);
        set("max_jingli", 20000);

        set("str", 100);
        set("int", 30);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 1200);
        set_skill("sword", 1200);
        set_skill("parry", 1200);
        set_skill("dodge", 1200);
        set_skill("force", 1200);

        set("jiali", 200);

        set_temp("apply/attack", 300);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIW "$N" HIW "���һ����һ�����������"
                       "���������ƻá�\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$Nɨ��$nһ�ۣ�û����$n��\n",
                       this_object(), ob);
        return 0;
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
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIY "$N" HIY "��������һ����⣬��ʱ��$n"
               HIY "������ľ���ֽ�����\n" NOR;
}

void unconcious()
{
        die();
}

varargs void die(object killer)
{
        object ob;
        string str;
        string* prize = ({
                "/clone/fam/etc/longjiao",
                "/clone/fam/etc/longjin",
                "/clone/fam/etc/longlin",
                "/clone/fam/etc/longxu",
        });
        str = prize[random(sizeof(prize))];
        ob = new(str);
        command("chat ѽ���벻������Ҳ����������ģ�");
        message_sort(HIR "$N" HIR "��һ����Ѫ�����ƶ�ȥ��ֻ��������һ��"
                     "���죬$N"HIR"\n������һ"+query("unit", ob)+
                     ob->name() + HIR "��\n", this_object());

        if (objectp(killer)) set("who_get", ([ "id"    : query("id", killer),
                                               "time"  : time() + 60]), ob); // 60����ֻ����ɱ���ҵ�ID��

        ob->move(environment());
        // ������ͼ
        // ���32
        if (random(10) == 1)
        {
                int n_tt;
                object ob_tt;
                n_tt = 32;
                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                if (ob_tt)
                {
                        write(HIG "��~~һ�ŵ�����ͼ��Ƭ���ڵ��ϡ�\n" NOR);
                        ob_tt->move(environment());
                }
        }

        // 1/600���ʵ�������ͭ��
        if (random(600) < 1)
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren" + (1 + random(2)));
                message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time() + 30, ob_tongren); // 30���ڶ����ܼ�ȡ
                ob_tongren->move(environment(this_object()));
        }
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N����ææ�����ˡ�\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "��˵" + name() + HIM "�������ã�Ԫ���ָ���"
                        "�Ѿ���Ȼ������硣" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
