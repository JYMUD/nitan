// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("jinyu-quan", 1) < 80)
                return notify_fail("��Ľ���ȭ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "jinyu-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "jinyu-quan")
                return notify_fail("��û��׼������ȭ��������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "˫ȭ�׷ɣ�������磬��ʱ�ó�һƬȭӰ���ƺ�$n"
              HIY"��ȫ����ȭӰ�����֡�\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");

                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "���ֻ�����������顱�������죬$p"
                                           HIR "ǰ�ر�$P" HIR "������ȭ����ʱŻ��"
                                           "һ����Ѫ��\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
