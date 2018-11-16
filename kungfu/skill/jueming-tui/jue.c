// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "����һ��" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, pp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("jueming-tui", 1) < 80)
                return notify_fail("������ȷ�������죬����ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("unarmed") != "jueming-tui")
                return notify_fail("��û�м��������ȷ�������ʩչ"+name()+"��\n");

        if (me->query_skill_prepared("unarmed") != "jueming-tui")
                return notify_fail("��û��׼�������ȷ�������ʩչ"+name()+"��\n");

        if( query("neili", me)<200 )
                return notify_fail("��Ŀǰ����������������ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch (random(3))
        {
        case 0:
                msg = HIR "ֻ��$N" HIR "һ����ߣ�������ߣ����Ⱥ�"
                      "ɨ��$n" HIR "�������������ɵ���\n" NOR;
                break;

        case 1:
                msg = HIR "$N" HIR "��ش��һ�����������߶�����ֱ"
                      "��$n" HIR "���ʣ���ʽ��ΪѸ�͡�\n" NOR;
                break;

        default:
                msg = HIR "ͻȻֻ��$N" HIR "˫�������߳���Ю������"
                      "��������ǧ��֮��ɨ��$n" HIR "��\n" NOR;
                break;
        }

        ap = attack_power(me, "unarmed") + me->query_str();
        dp = defense_power(target, "dodge") + target->query_dex();
        pp = defense_power(target, "parry") + target->query_str();

        if (ap / 2 + random(ap) < pp)
        {
                msg += HIC "����$n" HIC "����һ�Σ�Ӳ������ס��$N"
                       HIC "��һ�ȡ�\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "ȴ��$n" CYN "�򶨵����һ�ݣ�������$N"
                       CYN "��һ�ȡ�\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "��æ�񵲣�ȴֻ����������"
                                           "�ó��棬��ʱ��һ���ߵ÷���\n" NOR);
                me->start_busy(2);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
