// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "��Ԩʽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 130)
                return notify_fail("�����ң��÷�ֵȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIB "$N" HIB "���ּ��裬ʩ����ң��÷�֡���Ԩʽ�����ַ�"
              "��翣�����ʵʵ����$n" HIB "Ҫ����\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "��ʱ������Ӱ��Ϊһץ��$p" HIR "��"
                                           "�ܲ�������$N" HIR "��ָ�������ţ���Ѫ"
                                           "�Ĵ��ɽ���\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -50, me);
                msg += HIC "����$p" HIC "�������ݣ����μ�ת������Ķ����$P"
                       HIC "�Ĺ�����\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}