#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "�˷��ص���" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;

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

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 180)
                return notify_fail("��ĺ��ҵ����������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("��û�м������ҵ���������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����Գ�ۣ�ʩ����ս�˷��ص�ʽ�������е�" + weapon->name() +
              HIW "�������£��仯Ī�⣬������$n" HIW "����Ҫ����\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "������ʵ���Ǳ��Ī�⣬���ɵ���"
                       "�����⣬��ʽ��ʱ����������\n" NOR;
                count = me->query_skill("hujia-daofa", 1);
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ����������С�Ľ��С�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -220, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}
