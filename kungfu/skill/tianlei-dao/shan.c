#include <ansi.h>
#include <combat.h>

string name() { return HIW "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wn;
        int ap, dp;
        int i, attack_time;
        int count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() +"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("tianlei-dao", 1) < 150)
                return notify_fail("�����׾���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "tianlei-dao")
                return notify_fail("��û�м������׾���������ʩչ" + name() + "��\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        wn = weapon->name();

        msg = HIY "\n$N" HIY "������" + wn + HIY "������ǰ��ʩ�����С�" HIW "��"
              "������" HIY "����$N����Ȼ�ӿ죬\n����" + wn + HIY "���������嵶��"
              "����֮������˷�����˼��\n" NOR;

        message_combatd(msg, me, target);

        attack_time = 5;

        ap = attack_power(me,"blade");
        dp = defense_power(target, "dodge");

        addn("neili", -180, me);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 15;
                msg = HIG "$n" HIG "��$P" HIG "����������ӿ���Ʋ���"
                     "������$N" HIG "�����������ˡ�\n" NOR;
        } else
        {
                count = 0;
                msg = HIC "$n" HIC "��$N" HIC "�⼸������Ѹ���ޱȣ���"
                      "��������ֻ��С��Ӧ����\n" NOR;
        }

        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 15);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
