#include <ansi.h>
#include <combat.h>

#define JISHI "��" HIB "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/weituo-zhang/jishi", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JISHI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(JISHI "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("weituo-zhang", 1) < 120)
                return notify_fail("��Τ���Ʋ�����죬����ʩչ" JISHI "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���Ϊ����������ʩչ" JISHI "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" JISHI "��\n");

        if (me->query_skill_mapped("strike") != "weituo-zhang") 
                return notify_fail("��û�м���Τ���ƣ�����ʩչ" JISHI "��\n");

        if (me->query_skill_prepared("strike") != "weituo-zhang")
                return notify_fail("��û��׼��Τ���ƣ�����ʩչ" JISHI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIB "ֻ��$N" HIB "˫��һ����������������������ƣ�һ����"
              "��$n" HIB "��ȥ��\n" NOR;

        if (random(me->query_skill("strike")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("strike");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "$n" HIR "һ������$N" HIR "�ƾ����صĻ�"
                                           "����ǰ����ʱŻ��һ����Ѫ��\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
