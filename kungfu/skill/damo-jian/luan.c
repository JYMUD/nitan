// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "��Ħ������" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

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
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("damo-jian", 1) < 250)
                return notify_fail("���Ħ����������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("��û�м�����Ħ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "��ת���棬����" + weapon->name() +
              HIM "�Ϲ⵴�����������������ν�������$n"
              HIM "ȫ��\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "force") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 95,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "����$n" CYN "�������ʹ��$P"
                       CYN "��һ��û�����κ����á�\n" NOR;
                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("damo-jian", 1);

        target->affect_by("damo_luanqi",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "��ʱ$n" HIR "��ͷһ���Ի����ڵ�������ʱ"
                "����ʹ�����Ĵ����ߡ�\n" NOR;
}
