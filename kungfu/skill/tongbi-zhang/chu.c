#include <ansi.h>
#include <combat.h>

string name() { return HIM "�����Ⱥ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tongbi-zhang", 1) < 80)
                return notify_fail("��ͨ�������Ʋ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "tongbi-zhang")
                return notify_fail("��û��׼��ͨ�������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 80)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<120 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "�ڿն���ʩչ�����С�" HIM "�����Ⱥ" HIC "����"
              "����һֻ�����ٿն��£�˫���͵�����$n" HIC "��\n" NOR;
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage , 35,
                                           HIR "����$N" HIR "˫���������Ʒ����죬"
                                           "����Ѹ���ޱȡ�$n" HIR "�پ��ľ���ս��\n"
                                           "�����м�֮����΢�����ɼ�$N" HIR "����"
                                           "������$n" HIR "�ؿڣ��ٽ�$p����������"
                                           " \n" NOR);

                me->start_busy(1 + random(2));
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "��$N" CYN "��������������"
                      "��ӯ��ֻ�����һ�ݣ��Ŷ����һ�ơ�\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}