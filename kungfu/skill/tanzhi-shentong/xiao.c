#include <ansi.h>
#include <combat.h>

string name() { return HIG "Х�׺�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 200)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "ͻȻ��$N" HIG "ָ��һת������ָ�⡰�͡��ĵ���һ����â��ֱϮ$n"
              HIG "������Ѩ��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        damage = damage_power(me, "finger");

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                target->receive_damage("jing", damage + fmsk / 2, me); 
                target->receive_wound("jing", damage / 2 + fmsk / 3, me); 
                addn("neili", -damage*3, target);

                if( query("neili", target)<0 )
                        set("neili", 0, target);

                msg += HIR "$n" HIR "ֻ��$N" HIR "ָ��Ϯ�壬�漴����һ"
                       "��������ٸ�������ɢ�������ʡ�\n" NOR;
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�������ܣ������Ż�����ʱ��$P"
                       CYN "�Ĺ��ƻ�Ϊ���С�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
