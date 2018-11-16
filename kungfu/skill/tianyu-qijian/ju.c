// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "�۽���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("tianyu-qijian", 1) < 130)
                return notify_fail("��������潣������죬����ʩչ" + name() + "��\n");

        if (me->query_skill("force", 1) < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "��������һ�������е�" + weapon->name() +
              HIR "����һ���ʺ磬�⻪ѣĿ��������$n" HIR "��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "ֻ��$N" HIR "������Ϊһ�ߣ�����$n"
                                           HIR "��$p" HIR "ֻ��һ���������Ķ�����"
                                           "��ͷһ����Ѫ���������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�͵���ǰһԾ,������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
