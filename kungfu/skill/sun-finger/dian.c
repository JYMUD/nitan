// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��ָ��Ѩ" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("sun-finger", 1) < 120)
                return notify_fail("��һ��ָ��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 120)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("��û�м���һ��ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("��û��׼��һ��ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һ��ָ����������Ȼ���һָ���仯��ˣ��ɱ�$n"
              HIR "���Ѩ��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR "�Ƶ���"
                       "�ܲ�����һʱ�޷�������\n" NOR;
                target->start_busy((int)me->query_skill("finger") / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "�ı仯��"
                       "С���мܣ���ס��$P" CYN "�Ľ�����\n" NOR;

        }
        me->start_busy(2);
        message_combatd(msg, me, target);

        return 1;
}
