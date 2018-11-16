// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("mingwang-jian", 1) < 100)
                return notify_fail("�㲻��������������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("��û�м�������������������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���е�" + weapon->name() + HIW "����ݳ���"
              "����һ��������$n" + HIW "�������в�����Щ��ã��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ͷһ��һʱ��Ȼ���Ե��У�������"
                       "����������\n" NOR;
                target->start_busy(ap / 100 + 2);
                me->start_busy(1);
        } else
        {
                msg += HIC "����$n" HIC "����ֻ����΢һ�ͣ��漴���ѣ�û"
                       "�б�$P" HIC "�����š�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
