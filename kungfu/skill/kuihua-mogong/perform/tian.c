// wu.c �޷�����
// �������߿��֣������ý������붼����

#include <ansi.h>

inherit F_SSERVER;

#define WU "��" HIC "�޷�����" NOR "��"
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i, ap, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(WU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( query("neili", me)<340 )
                return notify_fail("��������������޷�ʩչ" WU "��\n");

        if ((lvl = me->query_skill("kuihua-mogong", 1)) < 220)
                return notify_fail("��Ŀ���ħ����򲻹����޷�ʩչ" WU "��\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("�㻹û�м�������ħ��Ϊ�ڹ����޷�ʩչ" WU "��\n");  

        if( query("max_neili", me)<3400 )
                return notify_fail("���������Ϊ���㣬����ʩչ" WU "��\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" WU "��\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" WU "��\n");
        }

        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" WU "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" WU "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "Ĭ�˿���ħ�������α������ޱȣ������Ӳ�ͬ�ķ�λ��$n"
              HIR "�������У�\n" NOR;
        i = 5;
        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");
                
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ������ǰһ�����������ܶ���$N"
                       HIR "����Ӱ�����ɰ������⣬�������ˡ�\n" NOR;
                count = me->query_skill("kuihua-mogong", 1) / 7;
                addn_temp("apply/attack", count, me);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "���ÿ죬����"
                       "�ҵ�������æ������С��Ӧ�ԡ�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -i*30, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}