// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ѫצ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

         if ((int)me->query_skill("sougu-yingzhua", 1) < 60)
                return notify_fail("���ѹ�ӥצ��������죬����ʩչ" + name() + "��\n");

       if (me->query_skill_mapped("claw") != "sougu-yingzhua")
                return notify_fail("��û�м����ѹ�ӥצ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("claw") != "sougu-yingzhua")
                return notify_fail("��û��׼�����ѹ�ӥצ��������ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 80)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 220)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        msg = HIW "\n$N" HIW "��ת������˫�ֺ���צ�У�ʩ�����С�" HIR "��"
              "Ѫצ" HIW "����Ѹ���ޱȵ�ץ��$n" HIW "��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "����$N" HIR "˫צ������$n" HIR "�����ܲ������ؿڱ�$N" HIR
                                           "ץ��ʮ��Ѫ�ۡ�\n" NOR);

                me->start_busy(3);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "�����мܣ�����$N" CYN "���л��⡣\n" NOR;

                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}


