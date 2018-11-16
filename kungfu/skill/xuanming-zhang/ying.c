#include <ansi.h>
#include <combat.h>

#define YING "��" HIW "��Ӱ����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xuanming-zhang/ying", me) )
                return notify_fail("�㻹û�о�����ָ�㣬����ʹ��"YING"��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YING "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 100)
                return notify_fail("����ڤ���Ʋ�����죬����ʩչ" YING "��\n");

        if (me->query_skill_mapped("strike") != "xuanming-zhang")
                return notify_fail("��û�м�����ڤ���ƣ�����ʩչ" YING "��\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("��û��׼����ڤ���ƣ�����ʩչ" YING "��\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" YING "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" YING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        msg = HIC "\n$N" HIC "��Хһ����ʩ�����С�" HIW "��Ӱ����" HIC "����"
              "˫�Ʋ��Ϸ��ڣ��Ʒ���͸����������֮������$n" HIC "���֡�\n" NOR;
        message_sort(msg, me, target);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "�پ��������ˣ�һʱ���޴�Ӧ�ԣ�"
                      "��������$N" HIR "���Ʒ�֮�С�\n" NOR;

                target->start_busy(1 + ap / 80);
                me->start_busy(1);
                addn("neili", -180, me);
        } else
        {
                msg = CYN "$n" CYN "����$N" CYN "���޹���֮�⣬��"
                      "�Ǵ󵨷�������$N" CYN "���о������⡣\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        }
        message_vision(msg, me, target);

        return 1;
}
