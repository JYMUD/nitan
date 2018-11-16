// mie.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill("bluesea-force", 1) < 150)
                return notify_fail("����Ϻ�������������죬����ʹ����������\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("��û�м����Ʒ�Ϊ�Ϻ��������޷�ʩչ��������\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "����һ��������Ϊצ��Ѹ���ޱȵ�Ϯ��$n��\n";

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                ap = me->query_skill("bluesea-force");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                // if (dp >= 10000)
                if( query("max_neili", me)<query("max_neili", target)*2 )
                {
                        damage = damage_power(me, "strike");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                        HIR "$n" HIR "ֻ�����У������ޱȣ�����Ī�⣬"
                                        "����һ����ȴ��Ȼ�����һ������͸�Ƕ�����\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "��һ����ȫ������$n" HIR "�����󣬱�$N"
                                HIR "���ʵʵ��ץ��������Ѩ������������ʱ��ɢ��\n" NOR;
                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
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