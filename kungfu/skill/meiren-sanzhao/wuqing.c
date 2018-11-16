// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��Ů����"; }

int perform(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��Ů����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("unarmed", 1) < 120 )
                return notify_fail("��Ļ����Ʒ����𲻹�������ʹ����Ů���顣\n");

        if (me->query_skill_mapped("strike") != "meiren-sanzhao")
                return notify_fail("��û�м����������У�����ʩչ����Ů���项��\n");

        if (me->query_skill_prepared("strike") != "meiren-sanzhao")
                return notify_fail("��û��׼���������У�����ʩչ����Ů���项��\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ���δ��죬��������Ů���顣\n");

        if( query("neili", me)<400 )
                return notify_fail("����������̫��������ʹ����Ů���顣\n");

        msg = HIB "\n\n$N�����߶������ý����ݺ����飡\n" NOR;
        msg += HIY "\n$N����֧�ã���������ӳ�����̾һ�������ּ���֮�⣬������ʹ��ɱ�С�\n\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "ֻ���顢�顢���������죬$n����ֽɫ����Ѫ���硣\n" NOR);
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$p���һ�֣�����Ծ�𣬱��ܵķ�Ӧ��$p�ӹ��˽١�\n\n"NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_combatd(msg, me, target);
        return 1;
}

