#include <ansi.h>
#include <combat.h>

#define LEI "��" HIY "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/benlei-zhang/lei", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LEI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(LEI "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("benlei-zhang", 1) < 120)
                return notify_fail("������������ƻ�������죬����ʩչ" LEI "��\n");

        if (me->query_skill_mapped("strike") != "benlei-zhang")
                return notify_fail("��û�м������������ƣ�����ʩչ" LEI "��\n");

        if (me->query_skill_prepared("strike") != "benlei-zhang")
                return notify_fail("��û��׼�����������ƣ�����ʩչ" LEI "��\n");

        if( query("neili", me)<400 )
                return notify_fail("��������������������ʩչ" LEI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "ֻ��$N" HIY "�������ƣ�ƽƽ�Ƴ�����ʱ�Ʒ����ȣ�����"
              "Я���������֮���͹���$n" HIY "��ȥ��\n" NOR;
        
        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(3);

                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "���ֻ��$n" HIR "һ���ƺߣ�$N"
                                           HIR "�ƾ����ض��������ۡ������һ��"
                                           "����Ѫ��\n" NOR);
                addn("neili", -300, me);
        } else
        {
                me->start_busy(2);
                addn("neili", -200, me);
                msg += CYN "����$p" CYN "������$N" CYN
                       "����ͼ���㿪������ɱ�š�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}