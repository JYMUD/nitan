// This program is a part of NITAN MudLIB
// fugu.c ����������-���ǲ���

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ǲ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("�㲻�ǿ��֣�����ʹ�ø��ǲ���\n");

        if ((int)me->query_skill("jinshe-zhang", 1) < 100)
                return notify_fail("��Ľ����Ʋ�����죬����ʹ�ø��ǲ���\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�ø��ǲ���\n");

        if (me->query_skill_prepared("strike") != "jinshe-zhang")
                return notify_fail("������û��׼�������Ʒ����޷�ʹ�ø��ǲ���\n");

        msg = HIC "$N" HIC "���һ���������������һ̽��ס$n"
              HIC "������������ɱ�֣�\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
             
        if (target->is_busy() ||
            (ap / 2 + random(ap)) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);

                addn("neili", -150, me);
                me->start_busy(2);
                msg = HIR "���$n" HIR "��$N" HIR "���������ƣ�"
                      "�ڡ����ǲ����£�һʱ��Ȼ�޷����֣�\n" NOR;
        }
        else
        {
                me->start_busy(2);
                msg = CYN "����$p" CYN "ʶ����$P"
                      CYN "��һ�У�����һ�ͣ������˶Է����ơ�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
