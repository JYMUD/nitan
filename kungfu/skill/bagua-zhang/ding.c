#include <ansi.h>
#include <combat.h>


#define DING "��" HIY "���Ķ�" NOR "��"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if( userp(me) && !query("can_perform/bagua-zhang/ding", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(DING "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���Ϊ����������ʩչ" DING "��\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 80)
                return notify_fail("��İ����Ʋ�����죬����ʩչ" DING "��\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("��û�м��������ƣ�����ʩչ" DING "��\n");

        if (me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("��û��׼�������ƣ�����ʩչ" DING "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʩչ" DING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һת����Ʈ��$n" HIY "��󣬶�Ȼʩ��һ�С�����"
              "������������׶��ֱ��$n" HIY "����ҪѨ��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "���ܲ�������$P" HIR
                                           "���в��У��ƾ���ʱ͸�ض�����������Ѫ"
                                           "������ˤ����\n" NOR);
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