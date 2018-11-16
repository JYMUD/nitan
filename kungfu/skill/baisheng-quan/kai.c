#include <ansi.h>
#include <combat.h>

#define KAI "��" WHT "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        
        if( userp(me) && !query("can_perform/baisheng-quan/kai", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("ֻ�п��ֲ���ʩչ" KAI "��\n");

        if ((int)me->query_skill("baisheng-quan", 1) < 100)
                return notify_fail("��İ�ʤ��ȭ������죬����ʩչ" KAI "��\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("����ڹ���Ϊ����������ʩչ" KAI "��\n");

        if (me->query_skill_mapped("cuff") != "baisheng-quan") 
                return notify_fail("��û�м�����ʤ��ȭ������ʩչ" KAI "��\n");

        if (me->query_skill_prepared("cuff") != "baisheng-quan")
                return notify_fail("��û��׼����ʤ��ȭ������ʩչ" KAI "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" KAI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "������ĺ��ƣ�������󷴹�������һ����$n"
              WHT "��ȥ�����ǡ�" NOR + HIR "�������" NOR + WHT "����"
              "����\n" NOR;
              
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$n" HIR "���ܲ�����$N" HIR "˫"
                                           "ȭ����$p" HIR "ͷ�����࣬��ʱ������Ѫ"
                                           "���������ʡ�\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -60, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}