// This program is a part of NITAN MudLIB
// chan.c ���߲���

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���߲���"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����߲���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("���á����߲������б�����ȣ�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("staff") < 80)
                return notify_fail("����ȷ��������ң��޷�ʹ�á����߲�����\n");

        if (target->is_busy())
                return notify_fail("�Է���æ���أ��㻹�Ǽӽ������ɣ�\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "���е�" + weapon->name() +
              HIG "��ס�Ĳ���������һ�����ߣ�����$n" HIG "������׽����\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "�ֻ�֮��ֻ�������Ż�����Ͼ������\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += HIC "����$p" HIC "������$N" HIC
                       "�����У�����������������$P�Ĺ�����" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
