// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "���޾���ָ"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����޾���ָ��ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʹ�á����޾���ָ����\n");

        if (me->query_skill("force") < 250)
                return notify_fail("����ڹ�����Ϊ����������ʹ�á����޾���ָ����\n");

        if (me->query_skill("xiuluo-zhi", 1) < 150)
                return notify_fail("�������ָ��Ϊ������Ŀǰ����ʹ�á����޾���ָ����\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʹ�á����޾���ָ����\n");

        if (me->query_skill_mapped("finger") != "xiuluo-zhi")
                return notify_fail("��û�м�������ָ������ʹ�á����޾���ָ����\n");

        msg = HIB "$N��Ȼ��¶�׹⣬���α���쳣Ʈ�죬��$n" HIB
                  "���������߸���ͣ��$n" HIB "����ãʱ��$N" HIB
                  "ͻȻ��������\n��Ϣ��һָ������\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -350, me);

                msg += HIR "ֻ��$n" HIR "һ���ҽУ��Ա�����Ҫ����λ��ֻ������ǰһ�ڣ��ƺ��Կ�������Χ��һ�У�����ҡҡ��׹��\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -150, me);
                msg += CYN "����$n" CYN "������$N" CYN "����ͼ������"
                       CYN "���Ʈ�����ɣ��������һ������һ����\n"NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
