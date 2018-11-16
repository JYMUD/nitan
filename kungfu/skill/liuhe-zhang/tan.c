#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "����̽��" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("liuhe-zhang", 1) < 60)
                return notify_fail("��������Ʒ�������죬����ʩչ"+name()+"��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ"+name()+"��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("strike") != "liuhe-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ"+name()+"��\n");

        if (me->query_skill_prepared("strike") != "liuhe-zhang")
                return notify_fail("��û��׼�������Ʒ�������ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "�Ĳ�����˫����������Ȼ�䵥��쬵�̽����һ�С�����"
              "̽���ơ���$n" HIC "��ǰ���䣡\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");

                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "���$p" HIR "���ܲ�������$P" HIR
                                           "һ�������ؿڣ���ʱ������Ѫ����������"
                                           "��\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}