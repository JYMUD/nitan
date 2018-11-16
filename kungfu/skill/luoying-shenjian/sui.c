#include <ansi.h>
#include <combat.h>

string name() { return HIG "�沨����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("����Ӣ�񽣲�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("��û�м�����Ӣ�񽣣�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "����" + weapon->name() + HIG "��ת����Ļ���ƣ�������"
              "Χ�����������ѣ�����$n" HIG "�ķ���\n" NOR;

        addn("neili", -80, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "����͸$N" HIR "���а���������Գ��У���ʱ"
                       "��ʧ���Ȼ���\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "����$p" CYN "���Ų�æ�������˴���"
                       "��ʵ����û���ܵ����Ӱ�졣\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}