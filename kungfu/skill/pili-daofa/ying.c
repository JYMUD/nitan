// ying.c ������������Ӱ���ء�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, zhao;

        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                 return notify_fail("����Ӱ���ء�ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                 return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("pili-daofa", 1) < 120)
                 return notify_fail("�������������򲻹����޷�ʩչ����Ӱ���ء���\n");

        if( query("neili", me)<120 )
                return notify_fail("�����������������ʹ�á���Ӱ���ء���\n");

        msg = HIC "$N" HIC "�����䣬����" + weapon->name() + "����ƬƬ��Ӱ����$n" + HIC
              "һ����ȥ��\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if ( ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "ֻ��$p" HIR "һ���ҽУ�"
                      "���϶�ʱ������Ѫ��ģ������Ѫ������\n" NOR;
                zhao = 5;
                count = ap / 15;
        } else
        {
                msg += CYN "����$p" CYN "�����񵲣���$P" CYN
                       "�Ĺ������⡣\n" NOR;
                zhao = 0;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        for (i = 0; i < zhao; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
