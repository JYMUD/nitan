// This program is a part of NITAN MudLIB
// xian.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("shenlong-bashi", 1) < 100)
                return notify_fail("���������ʽ�ַ���������죬����ʹ���������֡�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹�������ʹ���������֡�\n");

        if( query("neili", me)<150 )
                return notify_fail("��������������������ʹ���������֡�\n");

        if (me->query_skill_mapped("hand") != "shenlong-bashi")
                return notify_fail("��û�м���������ʽ�ַ�������ʹ���������֡�\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "�����ḡ���������ģ��Ƶ��ǵ�������ײײ�ĳ���$n"
              HIG "��ͬʱ���־���һ�У�����֮����\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");

                if( !target->is_busy() )
                        target->start_busy(1);
                addn("neili", -125, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "�����ҵ���ȴû�ܵ�ס$P" HIR "�⿴������"
                                           "�������������$P" HIR "���صĻ��У��۵�����һ����Ѫ��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ������ĵ�ס��$P"
                       CYN "�Ľ�����\n" NOR;
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

