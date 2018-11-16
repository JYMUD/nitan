// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string name() { return HIW "̫��ͼ" NOR; }

int perform(object me, object target)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("taiji-quan", 1) < 250)
                return notify_fail("���̫��ȭ������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 300)
                return notify_fail("���̫������Ϊ�������ߣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("taoism", 1) < 300)
                return notify_fail("��ĵ�ѧ�ķ���Ϊ�������ߣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("������û�м���̫��ȭ������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "taiji-shengong")
                return notify_fail("������û�м���̫���񹦣�����ʩչ" + name() + "��\n");

        if( query("jing", me)<1000 )
                return notify_fail("�����ھ�������������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        msg = HIM "$N" HIM "��ȻһЦ��˫�����Ữ������Ȧ�ӣ���ʱ���ܵ���"
              "��������ԴԴ���ϵı�ǣ��������\n\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -1000, me);
        addn("jing", -1000, me);
        me->start_busy(3);
        ap = attack_power(me, "cuff") + me->query_skill("taoism", 1);
        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_skill("count", 1);
                if (ap > dp * 11 / 10) 
                {
                        switch (random(3))
                        {
                        case 0:
                                tell_object(obs[i], HIY "���֮�����ƺ��ص��˹�ȥ�����磬��"
                                                    "Ȼ���޷��������ң���Ȼ��ǰ��һ��\n"
                                                    "��ȫȻ����������ͷһ�ң�����һ���"
                                                    "ʹ�������������Կ��ƣ�\n" NOR);
                                break;
                        case 1:
                                tell_object(obs[i], HIW "����ǰһ�н�����ģ�������������ǵ�"
                                                    "���ɾ���Ȼ����ȴ������ϢԽ��Խ�ң�\n"
                                                    "��֫һ����ʹ������Ҫվ����ס��\n" NOR);
                                break;
                        default:
                                tell_object(obs[i], HIR "����ߺ�Ȼ����һ���������ۼ������"
                                                    "��紸����������㲻�����һ����\n"
                                                    "�������¶�����ʹ����ֻ�и������ȡ�\n" NOR);
                                break;
                        }
                        damage = damage_power(me, "cuff");
                        damage+= query("jiali", me);
                        if( damage < query("max_qi", obs[i])* (25 + random(6)) / 100 )
                                damage = query("max_qi", obs[i])* (25 + random(6)) / 100;

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage / 2, me);

                        if( damage < query("max_jing", obs[i])* (25 + random(6)) / 100 )
                                damage = query("max_jing", obs[i])* (25 + random(6)) / 100;

                        obs[i]->receive_damage("jing", damage, me);
                        obs[i]->receive_wound("jing", damage / 3, me);

                        p=query("qi", obs[i])*100/query("max_qi", obs[i]);

                        switch (random(3))
                        {
                        case 0:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "�����㵸���������ԣ���"
                                      "Ȼ���һ������Ѫ��ֹ��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        case 1:
                                msg = HIR "ȴ��" + obs[i]->name() +
                                      HIR "��ò���ݣ��ƺ�������ʲ"
                                      "ô����֮�£�����һ�Σ�Ż��������Ѫ��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "����������һ��������������"
                                      "а�����϶��ų���Ѫ����\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        if (! obs[i]->is_busy())
                                obs[i]->start_busy(3);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        addn("neili", -500, obs[i]);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIC "�㷢����ǰ�ľ����ƻ����棬��æ"
                                            "Ĭ���ڹ����������š�\n" NOR);
                        addn("neili", -200, obs[i]);
                }
                if( query("neili", obs[i])<0 )
                        set("neili", 0, obs[i]);
        }

        if (! flag)
                message_combatd(HIM "Ȼ��û���κ�������$N"
                               HIM "��Ӱ�졣\n\n" NOR, me, 0, obs);

        return 1;
}
