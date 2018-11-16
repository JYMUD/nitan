// This program is a part of NITAN MudLIB
// qian.c

#include <ansi.h>
#include <combat.h>

string name() { return HIR "Ǭ������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("wuliang-jian", 1) < 100)
                return notify_fail("�������������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "����" + weapon->name() + HIR "���"
              "��ৡ������Ľ�������ȥ�Ƽ��죬ȫȻ����$n" HIR "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "���$n" HIR "�赲��������ʱ��$N"
                                           HIR "ն���������˿ڼ��ǣ��಻���ԡ�\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                       CYN "$N" CYN "�Ľ��С�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
