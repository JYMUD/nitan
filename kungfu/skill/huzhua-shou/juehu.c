// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "������ץ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��" + name() + "��\n");

        if( userp(me) && query("shen", me)<10000 )
                return notify_fail(HIC "\n��������������ʩչ���У���ͻȻ�뵽����������"
                                   "��һ����룬���ò���;�����˹�����\n" NOR);

        if ((int)me->query_skill("huzhua-shou", 1) < 120)
                return notify_fail("��Ļ�צ�����ֲ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("claw") != "huzhua-shou")
                return notify_fail("��û�м�����צ�����֣�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("claw") != "huzhua-shou")
                return notify_fail("��û��׼��ʹ�û�צ�����֣��޷�ʹ��" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���һ��������Ϊצ��˫צ��������צӰ����������һ����$n"
              HIR "��Ҫ��ץȥ��\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "һ���Һ���û���м�ס$P"
                                           HIR "�����Ĺ��ƣ���ץ��Ƥ����룬��Ѫ�ɽ���\n" NOR);
                addn("neili", -200, me);
                addn("shen", -3000, me);
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                addn("neili", -100, me);
                addn("shen", -3000, me);
                msg += CYN "����$p" CYN "������$N"
                       CYN "����ͼ���㿪������ɱ�š�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
