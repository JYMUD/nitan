#include <ansi.h>
#include <combat.h>

#define YOU "��" HIG "�޺�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && me->query_skill("fuhu-quan",1)<100 && !query("can_perform/fuhu-quan/fuhu", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YOU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("�������ֲ���ʩչ" YOU "��\n");

        if ((int)me->query_skill("fuhu-quan", 1) < 60)
                return notify_fail("��ķ���ȭ���𲻹�������ʹ��" YOU "��\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���δ��죬����ʹ��" YOU "��\n");

        if( query("neili", me)<140 )
                return notify_fail("��������������������ʹ��" YOU "��\n");

        if (me->query_skill_mapped("cuff") != "fuhu-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" YOU "��\n");

        if (me->query_skill_prepared("cuff") != "fuhu-quan")
                return notify_fail("��û��׼������ȭ��������ʩչ" YOU "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "���ɹ��Σ����һ��ʩ�����С�" HIG "����ʽ" HIW "����"
              "һȭ�͵ػ���$n" NOR"��\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("parry") / 2)
        {
                me->start_busy(2 + random(2));

                damage = (int)me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);

                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40, 
                                           HIR "����$N" HIR "һȭ�����ޱȣ�$n" HIR 
                                           "һʱ���޴��мܡ�\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������̩ɽ��̧��һ�ܸ���$P"
                       CYN "��һȭ��\n"NOR;
        }
        message_sort(msg, me, target);

        return 1;
}
