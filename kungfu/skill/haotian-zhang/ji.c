// haoran.c ��Ȼһ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��Ȼһ��"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ȼһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 60)
                return notify_fail("�������Ʋ�����죬����ʹ�ú�Ȼһ����\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ��Ȼһ����\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������޷�ʹ�ú�Ȼһ����\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("������û�м�������Ʒ����޷�ʹ�ú�Ȼһ����\n");

        if( query_temp("weapon", me) )
                return notify_fail("�������ֲ��ܹ�ʹ�ú�Ȼһ����\n");

        msg = HIC "$N" HIC "���һ����������$n" HIC "���ϣ�˫��"
              "ͬʱ����������һ�С���Ȼһ������\n" NOR;

        ap = attack_power(me, "strike");
        if (living(target))
                dp = defense_power(target, "dodge");
        else    dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -110, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "��$P" HIR "��������"
                                           "�㣬��æ���ˣ������$P" HIR "һ�ƻ�"
                                           "�˸����У���Ѫ��ֹ����\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -60, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}