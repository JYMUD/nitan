// kuang.c ��ɨ��Ҷ

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "��ɨ��Ҷ" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if( query("neili", me)<180 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("��Ŀ�罣���������ң��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("����Ṧ��Ϊ���㣬�޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ�������е�" + weapon->name() +
              HIC "�����缲��һ��������$n" HIC "��\n"
              HIR "��ʱ��ֻ�������������粨�˰���ӿ����$n"
              HIR "ֻ���ú�����ʱ������\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -150, me);

        count = me->query_skill("sword") / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
