// This program is a part of NITAN MudLIB
// he.c ˫������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "˫������"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("˫������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�������죬����ʹ��˫������\n");

        if ((int)me->query_skill("yunv-jian", 1) < 80)
                return notify_fail("�����Ů����������죬����ʹ��˫������\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 50)
                return notify_fail("���ȫ�潣��������죬����ʹ��˫������\n");

        if( query("neili", me)<400 )
                return notify_fail("����������̫��������ʹ��˫������\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("��û�м�����Ů����������ʹ��˫������\n");

        msg = HIY "$N" HIY "������ȫ�潣�����⣬���ֻ���Ů������"
              "�У�˫������ͬʱ�̳���\n" NOR;

        ap = attack_power(me, "sword");

        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "sword") +
                         (int)me->query_skill("quanzhen-jian", 1) +
                         (int)me->query_skill("yunv-jian", 1);

                addn("neili", -350, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "����$N" HIR "˫�����裬��ʽ������"
                                           "������Ϊ��һ����ȥ������֪����Ǻã�\n"
                                           HIR"һ��֮�£�$N" HIR "�Ľ����Ѿ���ʽ���룡$n"
                                           HIR "һ���ҽ�֮�£���ʱ�����ش���\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" NOR CYN "������$P" NOR CYN "����ͼ����"
                       "�Լ���ȫ�����»����ܲ�͸�磬��$P" NOR CYN "�޼ƿ�ʩ��\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
