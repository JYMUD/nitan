#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "ǧ�����" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("wudu-shenzhang", 1) < 100)
                return notify_fail("���嶾���Ʋ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang")
                return notify_fail("��û��׼���嶾���ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        msg = HIC "\n$N" HIC "����Ȼ��죬ʹ�����С�" HIG "ǧ�����" HIC "����"
              "˫�Ʋ����ĳ���\n��ʽ��Ӱ��ã���ʵ�Ѳ⣬��ͼ����$n" HIC "�Ĺ�"
              "�ơ�\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$n" HIY "ֻ��$N" HIY "˫��Ʈ����������"
                      "����������������$N" HIY "���Ʒ�֮�С�\n" NOR;

                if( !target->is_busy() )
                        target->start_busy(ap / 90 + 1);
                me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "����$N" CYN "���޹���֮�⣬��"
                      "�Ǵ󵨷�������$N" CYN "���о������⡣\n" NOR;

                me->start_busy(2);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}