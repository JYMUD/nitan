#include <ansi.h>
#include <combat.h>

string name() { return HIC "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 120)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��ָ�ᵯ����ʱֻ����쬡���һ����һ���������޵�"
              "����ѳ�$n" HIC "�����ȥ��\n" NOR;

        ap = attack_power(me,"finger");
        dp = defense_power(target,"parry");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                msg +=  HIR "$n" HIR "ֻ��в��һ�飬�ѱ�$P"
                        HIR "ָ�����У�ȫ����������������������\n" NOR;
                target->start_busy(ap / 80  + fmsk / 25); 
                me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������һԾ�����˿�ȥ��\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
