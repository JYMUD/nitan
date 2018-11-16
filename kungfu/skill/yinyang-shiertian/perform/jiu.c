#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "��תǬ��" NOR; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl, damage;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("neili", me)<900 )
                return notify_fail("��������������޷�ʩչ" +name()+ "��\n");

        if( query("max_neili", me)<9000 )
                return notify_fail("���������Ϊ��������ʹ��" +name()+ "��\n");

        if ((int)me->query_skill("force") < 900)
                return notify_fail("����ڹ���򲻹�������ʩչ" +name()+ "��\n");

        if ((lvl = (int)me->query_skill("yinyang-shiertian", 1)) < 810)
                return notify_fail("���������תʮ�����컹�����������޷�ʹ��" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(HIM "\n$N" HIM "����������תʮ�����죬�·��������������ʣ�"
                     HIM "�������Ͼ�ѧ" +name()+ HIM "��\n" NOR, me, target);

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge") + target->query_skill("yinyang-shiertian", 1);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                message_combatd(HIW "\n$N" HIW "����������Ю����֮�����ӿ�����$n"
                                HIW "����������\n" NOR, me, target);

                if (ap * 3 / 2 + random(ap) > dp)
                {
                        damage = damage_power(me, "force")*10;
                        if( query_temp("weapon", me) )
                        {
                                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, (i + 1) * 10 ,
                                                          HIR "���$n" HIR "����������$N" HIR
                                                          "���ھ���������룬$n��ͷһ�����һ��"
                                                          "����Ѫ��\n" NOR);
                        } else
                        {
                                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 10,
                                                          HIR "���$n" HIR "����������$N" HIR
                                                          "���ھ���������룬$n��ͷһ�����һ��"
                                                          "����Ѫ��\n" NOR);
                        }
                } else
                {
                        msg = CYN "$n" CYN "����˫�ۣ������мܣ���"
                              "$N" CYN "���ھ�ж����\n" NOR;
                }

                message_combatd(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }

        me->start_busy(2 + random(3));
        addn("neili", -1000-random(1000), me);
        return 1;
}

