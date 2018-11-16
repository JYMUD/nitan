#include <ansi.h>
#include <combat.h>

#define HONG "��" HIY "ս������" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/baihua-cuoquan/hong", me) )
                return notify_fail("�㻹û���ܵ�����ָ�㣬������ʹ��" HONG "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HONG "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("baihua-cuoquan", 1) < 250)
                return notify_fail("��İٻ���ȭ������죬����ʩչ" HONG "��\n");

        if ((int)me->query_skill("zhanshen-xinjing", 1) < 250)
                return notify_fail("���ս���ľ���Ϊ����������ʩչ" HONG "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" HONG "��\n");

        if (me->query_skill_mapped("unarmed") != "baihua-cuoquan")
                return notify_fail("��û�м����ٻ���ȭ������ʩչ" HONG "��\n");

        if (me->query_skill_mapped("force") != "zhanshen-xinjing")
                return notify_fail("��û�м���ս���ľ�������ʩչ" HONG "��\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("��û��׼���ٻ���ȭ������ʩչ" HONG "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����������������ʩչ" HONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ��ŭ������ս���ľ����˼�����˫ȭ��ʱЯ��"
              "�������֮���͹���$n" HIW "��\n" NOR;

        ap=me->query_skill("unarmed")+query("level", me)*20+
             me->query_skill("force") + me->query_skill("martial-cognize", 1);

        dp=target->query_skill("parry")+query("level", target)*20+
             target->query_skill("dodge") + target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        addn("neili", -100, me);
                        msg += HIR "ֻ��$N" HIR "һȭ�������㽫$n" HIR "���"
                               "�������飬�������һ����Ѫ������̱����\n" NOR
                               "( $n" RED "���˹��أ��Ѿ�������в�����ʱ��"
                               "���ܶ�����" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(4);
                        addn("neili", -600, me);
                        damage = damage_power(me, "unarmed");
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                                   HIR "���$p" HIR "���ܲ�����$P" HIR "��"
                                                   "ȭ���ƾ���ʱ͸����룬������Ѫ���磬��"
                                                   "��������\n" NOR);
                }
        } else
        {
                me->start_busy(5);
                addn("neili", -300, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {
                target->receive_wound("qi", 1, me);
                target->die(me);
        }

        return 1;
}