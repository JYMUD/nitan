// cui.c �߻�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "�߻�"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("���߻꡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("��ֻ�ܿ���ʹ�á��߻꡹������\n");

        ap = attack_power(me, "hand");

        if (ap < 150)
                return notify_fail("�����ħ�ֵȼ�����, �޷�ʹ�á��߻꡹��\n");

        if( query("neili", me)<150 )
                return notify_fail("��������������޷����á��߻꡹��\n");

        msg = HIR "$N" HIR "�������䣬���Һ����������������������˫����$n" HIR
              "�����ĵ���\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -120, me);
                damage = damage_power(me, "hand");
                target->receive_damage("jing", damage/3, me);
                target->receive_wound("jing", damage/5, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "���Ծ��ɣ��������ܣ���ʱ��"
                                           "�ĸ����š��ٸо��񲻼ã�ҡҡ������\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                addn("neili", -50, me);
                msg += CYN "$n" CYN "���������죬����һ�񣬷���������$N"
                       CYN "��һ�С�\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
