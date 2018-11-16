#include <ansi.h>
#include <combat.h>

#define REN "��" HIW "���ͬ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/liangyi-jian/ren", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(REN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" REN "��\n");

        if ((int)me->query_skill("liangyi-jian", 1) < 120)
                return notify_fail("�����ǽ���������죬����ʩչ" REN "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" REN "��\n");

        if (me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("��û�м������ǽ���������ʩչ" REN "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʩչ" REN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���г�����âԾ�������Ⱪ������������ƺ������Ҵ���$n"
              HIW "��$n" HIW "������\n��ƫ�󣬼�������ת����ֻ��һɲ������ɲʱϮ"
              "�����ף�\n";

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��æ��ת��ȴ����$N" HIR
                                           "��" + weapon->name() + HIR "������ת"
                                           "����ʱ���ض�����Ѫ��Ȫӿ��\n" NOR);
                addn("neili", -180, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "����һЦ��������ת���㿪��$P"
                       CYN "��ת�Ľ�ʽ������δ�ˡ�\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}