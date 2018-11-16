// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���־�" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 180)
                return notify_fail("��򹷰���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "ʹ���򹷰�����" NOR + WHT "��"
              HIG"���־�������"+query("name", weapon)+
              HIG "����ұƣ�������$n" HIG "��ȥ��\n" NOR;

        ap = attack_power(me, "staff") + me->query_int()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$n" HIR "ȫ��һ�������㲻�ȣ���$N"
                                HIR "���л��÷������صĵ����ڵ��ϡ�\n" NOR;

                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        set("eff_qi", 1, target);
                        set("eff_jing", 1, target);
                        target->unconcious(me);
                        return 1;
                } else
                {
                        damage = damage_power(me, "staff");
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "ֻ��$n" HIR "С�ȴ������͡�������"
                                           "�죬����$N" HIR "��" + weapon->name() +
                                           HIR "�������Ѫ����\n" NOR);
                        me->start_busy(3);
                        addn("neili", -200, me);
                }
        } else
        {
                msg += CYN "��$n" CYN "ȫ���������¶���������ʹ��$N"
                       CYN "�����޹�������\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
