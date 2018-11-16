#include <ansi.h>
#include <combat.h>

#define KOU "��" HIM "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/danding-dao/kou", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(KOU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" KOU "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ" KOU "��\n");

        if ((int)me->query_skill("danding-dao", 1) < 80)
                return notify_fail("��ĵ��ֵ����������ң�����ʩչ" KOU "��\n");

        if (me->query_skill_mapped("blade") != "danding-dao")
                return notify_fail("��û�м������ֵ���������ʩչ" KOU "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������ʩչ" KOU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "������Ȼһ�䣬ʱ������ʱ������ʱ������������磬ת˲"
              "��������$n" HIM "��\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "���$n" HIR "һ�������񣬱�����ɨ"
                                           "������Ѫ�Ľ���ʹ���ķΣ�\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "����$p" CYN "�����������ס�Ż�������$P"
                       CYN "�������У�ʼ���κβ��á�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}