// steal.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object env;
        object ob, victim;
        mapping myfam, vtfam;
        int sp, dp;

        env = environment(me);
        if( query("no_fight", env) )
                return notify_fail("�����ֹ���ԡ�\n");

        if( query("no_steal", env) )
                return notify_fail("�����ֹ���ԡ�\n");

        if( query_temp("stealing", me) )
                return notify_fail("���Ѿ����һ��������ˣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ��û��ʱ�䡣\n");

        if (! arg || sscanf(arg, "%s from %s", what, who) != 2)
                return notify_fail("ָ���ʽ��steal <��Ʒ> from <����>\n");

        victim = present(who, environment(me));
        if (! victim || victim == me)
                return notify_fail("�������ԵĶ��������\n");

        if( !me->visible(victim) )
                return notify_fail("�㿴����"+query("name", victim)+"��\n");

        if (! victim->is_character())
                return notify_fail("�㿴����ˣ��ǲ��ǻ��ˣ�");

        if( query_temp("sleeped", victim) )
                return notify_fail("����Ȼ��˯�����������Ի��Ǻܸߣ����޷����֣�");

        if (victim->query_competitor())
                return notify_fail("�˼����ڱ��䣬�㵷ʲô�ң�\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("��Ҳ���͵��ʦ���ϵĶ�����\n");

        if( query("jing", me)<80 )
                return notify_fail("���������Լ��о��񣬲���óȻ����͵�ԡ�\n");

        if (! ob = present(what, victim))
        {
                object *inv;
                inv = all_inventory(victim);
                if (! sizeof(inv))
                        return notify_fail(victim->name() + "���Ͽ�����û��ʲ"
                                           "��ֵǮ�Ķ�����͵��\n");
                ob = inv[random(sizeof(inv))];
        }

        sp = (int)me->query_skill("stealing") * 5 -
             query("thief", me)*20;

        if( (myfam=query("family", me)) && myfam["family_name"] == "ؤ��" )
                sp = (int)me->query_skill("stealing") * 10 -
                     query("thief", me)*20;

        if (sp < 1) sp = 1;

        if (me->is_fighting())
        {
                sp /= 2;
                me->start_busy(3);
        }
        dp=query("jing", victim)*2+ob->weight()/25;
        if (victim->is_fighting()) dp *= 10;
        if( query("equipped", ob))dp*=20;

        write("�㲻����ɫ����������" + victim->name() + 
              "���ȴ��������� ...\n\n");

        if( query("newbie", me) && playerp(victim) )
        {
                set("no_newbie", 1, me);
                delete("newbie", me);
                tell_object(me, HIR "������͵�����������Ʒ������ȡ����������ֱ�����\n" NOR);
        }

        set_temp("stealing", 1, me);
        me->start_call_out((: call_other, __FILE__, "compelete_steal", me, victim, ob, sp, dp :), 3);

        return 1;
}

void compelete_steal(object me, object victim, object ob, int sp, int dp)
{
        mapping myfam, vtfam;
        int steal_level;

        if (! objectp(me))
                return;

        delete_temp("stealing", me);

        if (! objectp(victim) || environment(victim) != environment(me))
        {
                tell_object(me, "̫��ϧ�ˣ������ֵ�Ŀ���Ѿ����ˡ�\n");
                return;
        }

        if( query_temp("sleeped", victim) )
        {
                tell_object(me, "����Ȼ��˯�����������Ի��Ǻܸߣ����޷����֣�\n");
                return;
        }

        if (! objectp(ob))
                return;

        if (environment(ob) != victim)
        {
                tell_object(me, "�����˰��죬����" + ob->name() +
                            "�Ѿ����������ˡ�\n");
                return;
        }

        if (! living(victim) || (random(sp + dp) > dp))
        {
                if( query_temp("is_riding", victim) == ob )
                {
                        tell_object(me, "��������" + victim->name() + "����" + ob->name() +
                                    "�������룬��������ʵʵ�ķ����֡�\n");
                        return;
                }

                if( query("no_steal", ob) )
                {
                        tell_object(me,"������һ"+query("unit", ob)+ob->name()+
                                    "��������ͻȻ�������飬��Ȼ�������֣����ǿ�ϧ�ˡ�\n");
                        return;
                }

                if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
                {
                        tell_object(me, "�ۿ����Ҫ���֣���ϧ���ϵĶ�"
                                    "��̫�࣬ʵ���ò����ˡ�\n");
                        ob->move(environment(me));
                        return;
                }

                if (! ob->move(me))
                {
                        tell_object(me,"������һ"+query("unit", ob)+ob->name()+
                                    "�����Ƕ������̫���ˣ����ò�������\n");
                        return;
                }

                tell_object(me, HIW "�����ˣ�\n\n" NOR);
                tell_object(me,"��ɹ���͵��һ"+query("unit", ob)+
                            ob->name() + "��\n");
                steal_level = (int)me->query_skill("stealing",1);

                if (living(victim))
                {
                        if (me->can_improve_skill("stealing"))
                                me->improve_skill("stealing",random(query("int", me)));

                        if( query("potential", me)<me->query_potential_limit() )
                        addn("potential", 1, me);

                        addn("thief", 1, me);
                        me->receive_damage("jing", 10);
                        addn("combat_exp", 1, me);
                }

                if (random(sp) < dp / 2)
                        message("vision", "�㿴��" + me->name() + "�������ش�" +
                                victim->name()+"����͵����һ"+query("unit", ob)+
                                ob->name() + "��\n", environment(me), ({ me, victim }));
        } else
        {
                if (random(sp) > dp / 2)
                {
                        tell_object(me, victim->name() + "�������һתͷ����"
                                    "��æ�������˻�ȥ��\n���ã�û�б����֣�\n");
                        return;
                }

                tell_object(me, HIR "��⣡��ʧ���ˣ�\n\n" NOR);
                message_vision("$Nһ��ͷ�����÷���$n������ץ��$P���ϵ�" +
                               ob->name() + "��\n$N�ȵ�������ʲô����\n",
                               victim, me);
                me->improve_skill("stealing", 1, 1);

                if (userp(victim))
                {
                        message_vision("$N�ݺݵ�����$n��ͷ���ŵ�$n����ֱ�С�\n",
                                       victim, me);
                } else
                {
                        victim->kill_ob(me);
                        me->fight_ob(victim);
                }

                if (! me->is_busy()) me->start_busy(3);
                addn("thief", 1, me);
                me->receive_damage("jing", 15 + random(10));
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ : steal <ĳ��> from <ĳ��>

���ָ�������л���͵���������ϵĶ������ɹ���, ��Ȼ����ܻ��
������Ʒ������, ����ʧ��, ������ʧ���ʱ��, ����ʧ��ʱ��Ȼ��
�ø�������, �����ʲô����......�����Լ�ȥ�����ޡ�
HELP );
        return 1;
}