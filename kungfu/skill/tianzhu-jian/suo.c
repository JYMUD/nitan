#include <ansi.h>
#include <combat.h>

#define SUO "��" HIW "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wp, wp2;
        object weapon, weapon2;
        int ap, dp;

        if( userp(me) && !query("can_perform/tianzhu-jian/suo", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SUO "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("tianzhu-jian", 1) < 120)
                return notify_fail("����������������죬����ʩչ" SUO "��\n");

        if (me->query_skill_mapped("sword") != "tianzhu-jian")
                return notify_fail("��û�м�����������������ʩչ" SUO "��\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" SUO "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" SUO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wp = weapon->name();
        ap = me->query_skill("tianzhu-jian", 1);
        dp = target->query_skill("parry", 1);

        if( query("max_neili", me)>query("max_neili", target)*3/2
            && objectp(weapon2=query_temp("weapon", target)) )
        {
                wp2 = weapon2->name();

                msg = HIW "\n$N" HIW "������Ȼ��죬ʩչ��������������������" +
                      wp + HIW "����һ����â������$n" HIW "���ֵ�" + wp2 + HIW
                      "��" NOR;

                message_sort(msg, me, target);

                       me->start_busy(2);
                       addn("neili", -200, me);

                if (random(ap) > dp / 2)
                {
                        msg = HIR "$n" HIR "ֻ����ǰ��â���ǣ���ʱ����һ�ᣬ"
                              + wp2 + HIR "�����ַɳ���\n" NOR;

                        target->start_busy(3);
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "����$n" CYN "����$N" CYN "�����е����У���"
                               "�����磬����Ӧ�ԡ�\n" NOR;
                }
        } else
        {
                msg = HIC "\n$N" HIC "������Ȼ��죬ʩչ����" HIW "��������"
                      HIC "��������" + wp + HIC "�����Ŀ������$n" HIC "������"
                      "����֮�С�" NOR;

                       me->start_busy(1);
                addn("neili", -100, me);

                if (random(ap) > dp / 2)
                {
                        msg += HIR "\n$n" HIR "���Ų�������ʱ������ţ���������$N"
                               HIR "�Ľ��⵱�С�" NOR;

                        target->start_busy(ap / 25 + 1);
                } else
                {
                        msg += CYN "\n����$n" CYN "����$N" CYN "�����е����У���"
                               "�����磬����Ӧ�ԡ�" NOR;
                }
        }
        message_combatd(msg, me, target);
        return 1;
}