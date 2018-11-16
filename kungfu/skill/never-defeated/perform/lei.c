// lei.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill("never-defeated", 1) < 150)
                return notify_fail("��Ĳ����񹦻�������죬����ʹ�����������\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("������ֱֳ��в���ʩչ���������\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ�������е�" + weapon->name() +
              HIC "�������£����Ƽ򵥣���Ȼ��ס��$n"
              HIC "���е���·��\n" NOR;

        ap = attack_power(me, "sword");
        dp = attack_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("never-defeated", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                if (dp >= 10000)
                {
                        damage = damage_power(me, "sword");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "ֻ�����У������ޱȣ�����Ī�⣬"
                                        "����һ����ȴ��Ȼ�����һ������͸�Ƕ�����\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "$n" HIR "ƽ����������������������ȫȻ�޷����⣬"
                                HIR "��ʱ����������Ҫ������Ȼ���أ�\n" NOR;
                        message_combatd(msg, me, target);
                        target->die(me);
                        return 1;
                }
        } else
        {
                msg += HIM "$n" HIM "���һ������æ���ҵֵ�����"
                                "Ȼû��һ���˺������ҵ��ѣ�\n" NOR;

                me->start_busy(1 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}