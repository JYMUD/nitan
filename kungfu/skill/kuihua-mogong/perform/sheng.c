// sheng.c ������Ϣ

#include <ansi.h>

inherit F_SSERVER;

#define XI "��" HIW "������Ϣ" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
                
        if ((int)me->query_skill("kuihua-mogong", 1) < 200)
                return notify_fail("��Ŀ���ħ��������񣬲���ʹ��" XI "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" XI "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷�ʩչ" XI "��\n");

        if (me->query_skill_mapped("dodge") != "kuihua-mogong")
                return notify_fail("�㻹û�м�������ħ��Ϊ�Ṧ���޷�ʩչ" XI "��\n");            

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���Ӻ������ˣ����ι����쳣����$n"
              HIR "���Ʈ��������\n" NOR;

        ap = attack_power(me, "dodge");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "ֻ�ܽ����Ż����������Գ�����\n" NOR;
                target->start_busy(ap / 120 + 2);
                addn("neili", -120, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "��������û"
                       "���ܵ��κ�Ӱ�졣\n" NOR;
                me->start_busy(1 + random(2));
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}