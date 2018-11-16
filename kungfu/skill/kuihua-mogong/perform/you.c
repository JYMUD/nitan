// you.c ��ڤһ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_skill("kuihua-mogong", 1) < 120)
                return notify_fail("��Ŀ���ħ����������죬����ʹ����ڤһ����\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʹ����ڤһ����\n");
                
        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("�㻹û�м�������ħ��Ϊ�ڹ����޷�ʩչ��ڤһ����\n");  
                 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR
              "������������Ȼ����$p��Ҫ����\n" NOR;
 
        ap = attack_power(me, "force") + me->query_dex();
        dp = defense_power(target, "parry") + target->query_dex();

        me->start_busy(1);
        addn("neili", -40, me);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
                       "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
                addn("neili", -60, me);
                damage = damage_power(me, "force") / 2 * 3;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                           HIR "$n" HIR "��æ���ˣ�������ң��������$N"
                                           HIR "���У���Ѫ����һ�أ�\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}