// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "���־�"; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_character() ||
            ! me->is_fighting(target))
                return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("wudang-zhang", 1) < 100)
                return notify_fail("����䵱���Ʋ�����죬����ʹ�����־���\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        msg = HIB "$N���˵��ʹ���������־���˫�Ʒ��������Ʒ磬����$n��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                        HIR "$n ãȻ��֪���룬�����$Nһ�ƻ���ǰ�أ�$n��ǰһ�ڣ������ɳ�����������\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", 200, me);
                me->start_busy(2);
                msg += HIG "����$p������$P����ͼ�����������һ�ߡ�\n" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}

