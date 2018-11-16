// Inherit: quarry.c ����
// Create by Vin for Heros.cn

#include <ansi.h>
inherit NPC;

int is_quarry()
{
        return 1;
}

void setup()
{
        if (query("aves"))
        {
                set("limbs", ({ "ͷ��", "����", "���", "�ҳ�",
                                "צ��", "β��" }));
                set("verbs", ({ "bite", "claw" }));
        } else
        {
                set("limbs", ({ "ͷ��", "����", "����", "����",
                                "ǰ��", "���", "β��" }));
                set("verbs", ({ "hoof", "bite", "claw" }));
        }
        set("race", "Ұ��");
        set("attitude", "aggressive");
        ::setup();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        // �Զ�����Ԧ�����ȼ����ߵ����
        if ((int)me->query_skill("training", 1) < 100 &&
            query_temp("owner") != query("id", me) &&
            !query("no_auto_kill"))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }

        remove_call_out("disappear");
        call_out("disappear", 15);
}

void disappear()
{
        object ob = this_object();

        // ���Ժ�����Ұ�޻��֮
        if (living(ob) && query("owner", ob))
        {
                message_vision(WHT "\nͻȻ$N" WHT "�͵�һ�ܣ�˲���"
                               "��ʧ����Ӱ���١�\n\n", ob);
                destruct(ob);
        }
}

void die(object killer)
{
        object me, item;
        object ob = this_object();
        int power, skill;
        string msg;

        if (query("aves"))
                message_vision(HIR "\nֻ��$N" HIR "�����˼��£��Ӱ�"
                               "����׹�����������ˡ�\n\n" NOR, ob);
        else
                message_vision(HIR "\nֻ��$N" HIR "���˼��������ڵ�"
                               "�������˼��£����ˡ�\n\n" NOR, ob);

        if (objectp(me = killer)
           || objectp(me = query_last_damage_from()))
        {
                // ���Ϊ�Լ����������֮
                // if (query("owner", ob) == query("id", me) &&
                if (
                   query("combat_exp", me) <= 5000000)
                {
                        // ���������趨�Ĳ��������轱��
                        power = query("power", ob);

                        if (power < 50)
                                power = 50;

                        if (power > 500)
                                power = 500;

                        GIFT_D->delay_bonus(me, ([ "prompt" : "ͨ�������ȡ" + ob->name() +
                                                              HIG "�ľ���",
                                                   "exp"    : random(power) + power,
                                                   "pot"    : random(power / 2) + power / 2,
                                                   "score"  : random(power / 4), ]));
                }
                skill = me->query_skill("hunting", 1);

                // �����Ʒ
                if (query("item1", ob) && random(skill) > 10)
                {
                        item = new(query("item1", ob));
                        item->move(me, 1);

                        msg = HIC "����ϸ��Ѱ" + ob->name() +
                              HIC "��ʬ�壬�����������һ" +
                              query("base_unit", item) +
                              item->name() + HIC;

                        // һ�����ʻ�ø߼���Ʒ
                        if (query("item3") && random(skill) > 60
                           && random(5) > 3)
                        {
                                item = new(query("item3"));
                                item->move(me, 1);

                                msg += "��һ" + query("base_unit", item) +
                                       item->name() + HIC;
                        } else
                        if (query("item2") && random(skill) > 30
                           && random(4) > 2)
                        {
                                item = new(query("item2"));
                                item->move(me, 1);

                                msg += "��һ" + query("base_unit", item) +
                                       item->name() + HIC;
                        }
                        msg += "��\n\n" NOR;
                        tell_object(me, msg);
                }
        }
        destruct(ob);
}
