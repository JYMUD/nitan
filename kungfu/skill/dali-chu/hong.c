#include <ansi.h>
#include <combat.h>

#define HONG "��" HIY "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wp;
        int ap, dp, damage;

        if( userp(me) && !query("can_perform/dali-chu/hong", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" HONG "��\n");

        if (me->query_skill_mapped("hammer") != "dali-chu")
                return notify_fail("��û�м������ϴ����ƣ�����ʩչ" HONG "��\n");

        if ((int)me->query_skill("dali-chu", 1) < 80)
                return notify_fail("�����ϴ����ƻ���㣬����ʩչ" HONG "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�����㣬����ʩչ" HONG "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ���㣬����ʩչ" HONG "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" HONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wp = weapon->name();

        msg = HIR "$N" HIR "�趯����" + wp + HIR "��һ�С�" HIY "�������"
              HIR "��Ю������ײ��֮����$n" HIR "��ͷ���£�\n" NOR;

        ap = me->query_skill("hammer");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "��$N" HIR "������ӿ����"
                                           "֪�������Ȼ������ܣ����ⴸ������"
                                           "�ڣ���Ѫ������\n" NOR);
                me->start_busy(3);

        } else
        {
                msg += CYN "����$p" CYN "��֪$P"
                       CYN "�д�һ�ţ����������мܣ��񵲿�����\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}