// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR "������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("chanhun-suo",1) < 70)
                return notify_fail("��Ĳ���������̫ǳ��ʹ����" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("����ڹ���򲻹���ʹ����" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (me->query_skill_mapped("whip") != "chanhun-suo")
                return notify_fail("��û�м�������������ʹ����" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("���������㣬�޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����Ц��ʹ���������������������������Ӱ����$n"
              HIR "ȫȫ���֣�\n\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "���$n" HIY "������ɽ������Ĺ������˸����ֲ�����������������ȫ�޷�����\n" NOR;
                target->start_busy(ap/120 + 2);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ������һ�ݣ��ӿ��˹��ơ���\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}