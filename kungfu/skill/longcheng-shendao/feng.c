#include <ansi.h>
#include <combat.h>

string name() { return HIW "���꽻��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("longcheng-shendao", 1) < 120)
                return notify_fail("��������񵶲�����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "longcheng-shendao")
                return notify_fail("��û�м��������񵶣�����ʩչ" + name() + "��\n");

        if( query("neili", me)<270 )
                return notify_fail("��Ŀǰ����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ����ʩ�����С�" HIW "���꽻��" HIC "����"
              "�е�" + weapon->name() + HIC "�����\nһ����$n" HIC "��ȥ��$n" HIC
              "��ͬС��һ���ڵ�����Ư��������\n" NOR;

        attack_time = 3;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        attack_time += random(ap / 40);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*25, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "�����Ʊ仯Ī�⣬$n" HIY "��ʱ�����ۻ����ң��޷��ֵ���\n" NOR;
                count = ap / 35;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "����������Ȼ�������а��С�ʹ����������ֵ���\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 20);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
