// bagua.c ������

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������â��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ı������ԡ�\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ������\n");

        if( query("neili", me)<400 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("zijinbagua-dao", 1) < 200)
                return notify_fail("����Ͻ���Ե��������ң��޷�ʹ�á�������â����\n");

        if (me->query_skill_mapped("blade") != "zijinbagua-dao")
                return notify_fail("��û�м����Ͻ���Ե����޷�ʹ�á�������â����\n");

        msg = MAG "$N" MAG "һ�����ȣ����е�" + weapon->name() +
              MAG "��â��������ʱֻ����������ĵ�â���հ������"
              "��λֱӿ$n" MAG "��\n\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "������ʵ���Ǳ��Ī�⣬���ɵ���"
                       "�����⣬��ʽ��ʱ����������\n" NOR;
                count = me->query_skill("zijinbagua-dao", 1) / 6;
        } else
        {
                msg += HIY "$n" HIY "�ĵ�΢΢һ����������С�Ľ��С�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5 + random(3) ; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}