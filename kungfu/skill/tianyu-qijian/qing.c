// qing.c ��˼��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��˼��"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����˼����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 70)
                return notify_fail("��������潣������죬����ʹ�á�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�ʵ��̫�û���á���˼������\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á���˼������\n");

        if (me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("��û�м��������潣��û���á���˼������\n");

        msg = HIG "$N" HIG "��������һ�������е�" + weapon->name() +
              HIG "����һ���ʺ磬�⻪ѣĿ��������$n" HIG "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -120, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "ֻ��$N" HIR "������Ϊһ�ߣ�����$n"
                                           HIR "��$p" HIR "ֻ��һ���������Ķ�����"
                                           "��ͷһ����Ѫ���������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�͵���ǰһԾ,������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
