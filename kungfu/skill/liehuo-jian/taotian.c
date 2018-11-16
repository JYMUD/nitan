// taotian.c �һ𽣷�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("���������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("liehuo-jian", 1) < 70)
                return notify_fail("����һ𽣷�������죬����ʹ�á��������졹��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");

        if ((int)query("neili", me) < 300)
                return notify_fail("��������������������ʹ�á��������졹��\n");

        if (me->query_skill_mapped("sword") != "liehuo-jian")
                return notify_fail("������û�м����һ𽣷�������ʹ�á��������졹��\n");

        msg = HIR "$N" HIR "���б���һ���������һ𣬷��Ҳ���������λ�������ο࣡\n\n"
              "ɲ�Ǽ�������»����죬�������˴���ǿ��������Ĵ������\n\n"
              "$N" HIR "��Ц�£������������" + weapon->name() + HIR "�϶�Ϊһ��ֱ��$n" HIR "��ȥ�����ƾ��ˣ�\n\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "sword");
                addn("neili", -200, me);
                me->receive_wound("qi",random(damage/3));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "ֻ��$N" HIR "����Ļ�⽫$n"
                                           HIR "����Χס��$n" HIR "�ĲҺ���"
                                           "����ë���Ȼ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�͵������һԾ��������$P" HIC "�Ĺ�����Χ��\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}