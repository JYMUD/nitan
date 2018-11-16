// lian.c ����������

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("�����ý�����ʩչ������������\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷�ʩչ������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ������������\n");

        if ((int)me->query_skill("xiyang-jian", 1) < 80)
                return notify_fail("����������������ң��޷�ʹ����������\n");

        if (me->query_skill_mapped("sword") != "xiyang-jian")
                return notify_fail("��û�м������������޷�ʹ����������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "\n$N" HIC "���һ����ֻ����һ������һ������һ������һ��������һ����һ�����$n"
              HIC "��\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(5));
        return 1;
}
