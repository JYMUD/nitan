#include <ansi.h>
#include <combat.h>

#define TONG "��" HIR "�ٹ�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/zhenyu-quan/tong", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(TONG "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("zhenyu-quan", 1) < 80)
                return notify_fail("������ȭ��������죬����ʩչ" TONG "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���Ϊ����������ʩչ" TONG "��\n");

        if (me->query_skill_mapped("cuff") != "zhenyu-quan") 
                return notify_fail("��û�м�������ȭ��������ʩչ" TONG "��\n");

        if (me->query_skill_prepared("cuff") != "zhenyu-quan")
                return notify_fail("��û��׼������ȭ��������ʩչ" TONG "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����ڵ���������������ʩչ" TONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���ֻӳ�һȭ��Ʈ�������Ļ���$n" HIR "�����ƾ���"
              "�Ű��������\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
                                           HIR "$n" HIR "ֻ������һ������֪$N" HIR
                                           "��ȭ���������ʱȭ�����£���\n�ض���"
                                           "��$n" HIR "��ʱŻ���������Ѫ��������"
                                           "�ʣ�\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "�к����ɱ�ţ��������Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}