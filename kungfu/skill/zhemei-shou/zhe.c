// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "��÷ʽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        skill = me->query_skill("zhemei-shou", 1);

        if (skill < 80)
                return notify_fail("�����÷�ֵȼ�����������ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 120)
                return notify_fail("���ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "����ң��÷�����仯Ϊһʽ����������ӳ�������"
              "ʵʵ����$n" HIC "ȫ���ҪѨ��\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        addn("neili", -80, me);
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg += HIR "$n" HIR "��ͷһ�����벻���ƽ�֮������æ��"
                      "��������һʱ���޷�������\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN "����ͼ��˿"
                      "����Ϊ��������$P" CYN "������û������κ����á�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}