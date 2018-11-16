// This program is a part of NITAN MudLIB
// po.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���־�"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("���á����־������б����е���\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 90)
                return notify_fail("��ĺ��ҵ���������죬����ʹ�á����־�����\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á����־�����\n");

        msg = HIM "$N" HIM "���е�" + weapon->name() +
              HIM "����һת��һ�����ε�����Ȼ��Ϣ��Ϯ��$n" HIM "��\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                           HIR "ֻ��$n" HIR "һ���ҽУ�����������"
                                           "�����������Ѫ���������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "Ĭ��������Ӳ�ǵֵ���$P"
                       HIC "��������ε�����\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}