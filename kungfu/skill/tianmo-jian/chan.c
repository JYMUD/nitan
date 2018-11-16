// chan.c ��ħ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��ħ����"; }

int perform(object me, object target)
{
        object weapon;
        int level, b;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����ħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (!living(target))
                return notify_fail("�Է��Ѿ�����ս���ˣ�\n");

        if ((level = me->query_skill("tianmo-jian", 1)) < 160)
                return notify_fail("�����ħ����������죬����ʹ�á���ħ������\n");

        if( query("neili", me)<80 )
                return notify_fail("�����������������޷�ʹ�á���ħ������\n");

        msg = HIM "$N" HIM "ʹ����ħ��������ħ������Ĭ�˿ھ���������"
              + weapon->name() + HIM "һ������ʱ����һ�������Ļ��������\n" NOR;

        addn("neili", -60, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(2) > dp)
        {
                msg += HIR "���$p" HIR "�پ����ǲ������������ң�"
                       "ȫȻ��֪���ںδ�������������\n" NOR;
                b = level / 20;
                if (b > 8)   b = 8;
                target->start_busy(b);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����æ"
                       "�˹�������ס��\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
