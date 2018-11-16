// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string name() { return HIW "ħ�����޼�" NOR; }

int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        me->clean_up_enemy();
        if (! me->is_fighting())
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (query("max_neili", me) < 8000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" + name() + "��\n");

        if (me->query_skill("jiuyang-shengong", 1) < 250)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 2000)
                return notify_fail("��������������޷�����" + name() + "��\n");

        msg = HIY "ֻ��$N" HIY "˫Ŀ΢�գ��������졣���Ķ�ʱ����һ���ޱȴ��۵�"
              "���ţ����ǰ�\n�塸" NOR + HIW "ħ�����޼�" NOR + HIY "������ʱ"
              "����������ɳ���𣬿������ȣ��������ڡ�$N" HIY "\n�漴��£����"
              "�����ű��ѿ����������ܵ����������â���Ժ��������ԡ�\n\n" NOR;

        message_combatd(msg, me);

        addn("neili", -1000, me);
        me->start_busy(5);

        ap = attack_power(me, "unarmed") + me->query_con();

        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_con();

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â��������һ��͸����롣\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â����ǧ��ϸ��һ����������㡣\n"
                                                    NOR);
                                break;
                        }

                        damage = attack_power(me, "force");
                        damage+= query("jiali", me);
                        damage *= 2;
                        damage+= random(damage);

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage, me);

                        obs[i]->receive_damage("jing", damage * 6, me);
                        obs[i]->receive_wound("jing", damage * 3, me);

                        p = (int)query("qi", obs[i]) * 100 / (int)query("max_qi", obs[i]);

                        switch (random(5))
                        {
                        case 0:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "һ���Һ�������������������"
                                      "�ۡ���Ż��һ�����Ѫ��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 1:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "���ɳ���Զ�����صĵ�����"
                                      "���ϣ������ս�����Ҳû����վ��"
                                      "��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "����ײײ�����������������"
                                      "�ڵء���ü������������һ�ɽ���"
                                      "��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "��â������" + obs[i]->name() +
                                      HIR "ȴ�Ǵ�����������Ҳ��������"
                                      "����Ѫ������Ť����ɷ�ǿֲ���\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "��æ������ˣ���ֻ����ǰ��"
                                      "â���ǣ�һ��������ȫ���Ѷ�����"
                                      "���˿ڣ���Ѫ�ɽ���\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        if (! obs[i]->is_busy())
                                obs[i]->start_busy(1);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        addn("neili", -500, obs[i]);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIY "��ֻ����ǰ����������Χ������"
                                            "�����ڣ���֮����æ�����ڹ�������"
                                            "������\n" NOR);
                }
                if (query("neili", obs[i]) < 0)
                        set("neili", 0, obs[i]);
        }

        if (! flag)
                message_combatd(HIY "ֻ����â������ȴû���κ��˱�$N"
                               HIY "���л��С�\n\n" NOR, me, 0, obs);

        return 1;
}
