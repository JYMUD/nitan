// shou.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define SHOU  "��" HIG "��������" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHOU "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("����ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("jiuyin-shengong", 1) < 260)
                return notify_fail("��ľ����񹦻�������죬����ʹ��" SHOU "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        if (me->query_skill_mapped("hand") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" SHOU "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��������һ���³���һ��������ʽ���أ�������ı���$n"
              HIY "��ҪѨ��\n";

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("jiuyin-shengong");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(3));

                me->want_kill(target);

                if (dp >= 10000) // ���ж�ǧ�������ϵ�����Ч
                { // ������Ȼ�ܵ��˺�
                        damage = damage_power(me, "hand");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "ֻ�����У������ޱȣ�����Ī�⣬"
                                        "����һ����ȴ��Ȼ�����һ������͸�Ƕ�����\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "��һ����ȫ������$n" HIR "�����󣬱�$N"
                                HIR "���ʵʵ�Ĵ�����̴�д�Ѩ������������ʱ��ɢ��\n" NOR;
                        message_combatd(msg, me, target);
                        addn("neili", -200, me);
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