// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "�콣��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "sword")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 120)
                return notify_fail("�����ң����������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("��û�м�����ң����������ʩչ" + name() + "��\n");

        if (query("neili", me) < 300)
                return notify_fail("��Ŀǰ����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "���һ����Х��ʩ����ѧ��" HIM "�콣��"
              HIW "��������" + weapon->name() + HIW "�������졣��ʱ��"
              "����Ľ�������ӿ����" NOR;

        attack_time = 4;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        level = me->query_skill("xiaoyao-jian", 1);
        attack_time += random(ap / 120);

        if (attack_time > 9)
                attack_time = 9;

        addn("neili", -attack_time*30, me);
        addn_temp("apply/attack", level, me);

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));
        addn_temp("apply/attack", -level, me);

        return 1;
}