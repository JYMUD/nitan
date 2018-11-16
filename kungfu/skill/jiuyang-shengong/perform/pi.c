// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��������" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && !query("can_learn/jiuyang-shengong/enable_weapon", me))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 220)
                return notify_fail("��ľ����񹦲�����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("����ڹ���������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("blade", 1) < 260)
                return notify_fail("��Ļ���������򲻹�������ʩչ" + name() + "��\n");

        if ((int)query("max_neili", me) < 5500)
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (query("neili", me) < 400)
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "jiuyang-shengong")
                return notify_fail("��û�м���������Ϊ����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "��Ȼ�������𣬰����һ����Х������ԴԴ������ӿ"
              "��" + weapon->name() + HIW "��ɲ�Ǽ䵶â��Ŀ��������£�����$n" HIW "��\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);

        me->start_busy(2 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85 + random(50),
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "����$n" HIC "��͸$P" HIC "����֮�е���������"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -(damage/4), target);
        addn("neili", -(damage/8), target);
        return  HIR "$n" HIR "ֻ����â��Ŀ������ԥ�䵽��â�Ѵ�͸$n" HIR "���壬��ʱ"
                "��Ѫ��ӿ����Ϣɢ�ҡ�\n" NOR;
}
