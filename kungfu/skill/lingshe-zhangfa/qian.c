#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "ǧ�߳���" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("������ֳ�һ���Ȳ���ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if ((lvl = (int)me->query_skill("lingshe-zhangfa", 1)) < 120)
                return notify_fail("��������ȷ��������ң��޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("��û�м��������ȷ����޷�ʹ��" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���һ����������ǰ�����е�" + weapon->name() +
              HIW "���������â��һ������$n" HIW "��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "��$N" HIY "��" + weapon->name() +
                       HIY "ʹ�û�����֣���������һ�㣬ʵ�������Եֵ���ֻ�к��ˡ�\n" NOR;
                count = lvl / 20;
                addn_temp("apply/attack", count, me);
        } else
                count = 0;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
