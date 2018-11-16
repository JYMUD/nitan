#include <ansi.h>
#include <combat.h>

#define PAN "��" HIR "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/panyang-zhang/pan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("panyang-zhang", 1) < 60)
                return notify_fail("��������Ʋ�����죬����ʩչ" PAN "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ" PAN "��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʩչ" PAN "��\n");

        if (me->query_skill_mapped("strike") != "panyang-zhang")
                return notify_fail("��û�м��������ƣ�����ʩչ" PAN "��\n");

        if (me->query_skill_prepared("strike") != "panyang-zhang")
                return notify_fail("������û��׼��ʹ�������ƣ�����ʩչ" PAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "һ���Ϻȣ�˫�Ʒ׷ɣ�һʽ���������¡���"
              "��������$n" HIR "��ȥ��\n" NOR;
        
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "���ܲ�������$P" HIR
                                           "�����������ƣ���ʱ������Ѫ����������"
                                           "��\n" NOR);
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