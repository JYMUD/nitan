#include <ansi.h>
#include <combat.h>

string name() { return HIC "������Ѩ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("lanhua-shou", 1) < 120)
                return notify_fail("��������Ѩ�ֲ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("��û�м���������Ѩ�֣�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") != "lanhua-shou")
                return notify_fail("��û��׼��������Ѩ�֣�����ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "�������������ָ����ת��һ��ʢ�������������$n"
              HIC "в��ҪѨ��\n";

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIR "$p" HIR "ֻ��в��һ�飬�ѱ�$P"
                        HIR "������ţ���ʱȫ����������������\n" NOR;
                target->start_busy(ap / 100 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������һԾ�����˿�ȥ��\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
