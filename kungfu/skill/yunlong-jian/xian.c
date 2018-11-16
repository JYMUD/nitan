// xian.c  ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if ((int)me->query_skill("yunlong-jian", 1) < 50)
                return notify_fail("�����������������죬����ʹ�á��������֡���\n");
                                
        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʹ�á��������֡���\n");
                        
        if( query("neili", me)<300 )
                return notify_fail("��������������������ʹ�á��������֡���\n");
                        
        msg = HIM "$N" HIM "΢΢һЦ������һ����������Ԧ����������ʵʵ�Ĺ���$n"
              HIM "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "ֻ��$N" HIR "���н������һ���������ڿն�"
                                           "��ٿ������$n" HIR "��\n$p" HIR "ֻ��һ�ɴ���"
                                           "����ǵذ�ѹ������ʱ��ǰһ���������������۵�"
                                           "���һ����Ѫ����\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�͵���ǰһԾ��������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
