// This program is a part of NITAN MudLIB
// rou.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "���־�" NOR; }

int perform(object me, object target)
{
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

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("��Ҫʩչȭ������ʹ��������\n");

        if ((int)me->query_skill("lingshe-quan", 1) < 120)
                return notify_fail("�������ȭ��������죬���ڻ��޷�ʹ�á����־�����\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������޷����á����־�����\n");

        msg = HIG "$N" HIG "һȭ�������;���ֱۺ�Ȼ����˼���ת�˸�Ȧ�ӣ�����$n"
              HIG "����$p" HIG "����ʤ����\n"NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                if (!target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "cuff");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "ֻ��$n" HIR "���һ�����ֻ�֮�²������㣬��$N"
                                           HIR "һȭ���˸����У��ƺ�һ��������������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����Ŀ죬��æʩչ�����ܿ���ȭ��\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}