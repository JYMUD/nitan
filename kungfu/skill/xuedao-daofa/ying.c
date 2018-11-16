// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ӱ��" NOR; }

inherit F_SSERVER;

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
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 120)
                return notify_fail("���Ѫ���󷨻������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("��û�м���Ѫ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "һ����Ц�������е�" + weapon->name() +
              WHT "�趯���֣����漤����" HIR "Ѫ��" NOR +
              WHT "����$n" WHT "��ȥ��\n" NOR;

        addn("neili", -80, me);
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "���$p" HIR "��$P" HIR "�Ƶ���æ��"
                       "�ң�ֻ�ܽ����Ż��������ö���\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ"
                       "���������ţ�Ӧ�����硣\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
