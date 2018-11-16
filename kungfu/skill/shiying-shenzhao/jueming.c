// jueming.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "����"; }

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
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("��ֻ�ܿ���ʹ�á���������\n");

        ap = attack_power(me, "claw");

        if (ap < 150)
                return notify_fail("���߱ӥ��צ�ȼ�����, �޷�ʹ�á���������\n");

        if( query("neili", me)<180 )
                return notify_fail("��������������޷����á���������\n");

        msg = HIR "$N" HIR "һ�����ȣ��ֱ������ͻ������һ�Σ����ֳ�צ����$n" HIR
              "ǰ��Ѹ��ץ����\n" NOR;

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "���ܲ�����ǰ�ض�ʱ��ץ��"
                                           "����Ѫ�ۣ����������Һ���\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                damage = damage_power(me, "claw") / 5;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIM "$n" HIM "����С����У�ƴ����⣬"
                                           "��˫���Ա�ץ���˼���Ѫӡ��\n" NOR);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
