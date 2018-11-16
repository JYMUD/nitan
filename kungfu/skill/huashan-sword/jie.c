// This program is a part of NITAN MudLIB
// jie.c ��ɽ����������ʽ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "����ʽ" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if ((level = me->query_skill("huashan-sword", 1)) < 30)
                return notify_fail("��Ļ�ɽ����������죬�޷�ʩչ" + name() + " ��\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("��û�м�����ɽ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<60 )
                return notify_fail("�����������������޷�ʹ�á�����ʽ����\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n����$N" HIW "����һ�գ�ʹ����ɽ��������֮"
              "��" HIG "����ʽ" HIW "����ת��֮�������޷죬һ\n"
              "���ȳ�������ԴԴ��к�������Ծ̲����������Ѹ"
              "Ȼ����$n" HIW "��\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "�᲻��������������"
                       "������һʱ���޷����֣�\n" NOR;
                target->start_busy(level / 80 + 3);
        } else
        {
                if( objectp(weapon=query_temp("weapon", target)) )
                        msg += CYN "����$p" CYN "ʶ����$P" CYN "�����⣬"
                               "�Թ˽����е�" + weapon->name() +
                               CYN "���һ�Ź⻨��$P"
                               CYN "һ��֮����Ҳ������ȥ��\n" NOR;
                else
                        msg += CYN "����$p" CYN "˫�ִ�����ģ���$P"
                               CYN "������һһ�ܿ���\n" NOR;

                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
