#include <ansi.h>
#include <combat.h>

#define DIAN "��" HIM "�ڵ�Ǭ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/hexing-bifa/dian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "dagger" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" DIAN "��\n");

        if ((int)me->query_skill("hexing-bifa", 1) < 100)
                return notify_fail("��ĺ��αʷ�������죬����ʩչ" DIAN "��\n");

        if (me->query_skill_mapped("dagger") != "hexing-bifa")
                return notify_fail("��û�м������αʷ�������ʩչ" DIAN "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��Ŀǰ����������������ʩչ" DIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "�����죬����" + weapon->name() + HIW "һ�"
              "ʩ�����С�" HIM "�ڵ�Ǭ��" HIW "������Ȼ�䣬" + weapon->name() + HIW
              "��������$n" HIW "����ҪѨ��" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*30, me);


        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}