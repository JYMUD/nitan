#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "����ʴ��"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ʴ�¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("ranmu-daofa", 1) < 180)
                return notify_fail("���ȼľ����������죬����ʹ�û���ʴ�¡�\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹�������ʹ�û���ʴ�¡�\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ̫��������ʹ�û���ʴ�¡�\n");

        if( query("neili", me)<600 )
                return notify_fail("����������̫��������ʹ�û���ʴ�¡�\n");

        if (me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("��û�м���ȼľ����������ʩչ����ʴ�¡�\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "����" + weapon->name() + HIR "һ���������ʱ����"
                        "�������棬��ԡ������һ��ϯ��$n" HIR "ȫ��\n"NOR;

        me->start_busy(2 + random(2));
        ap = attack_power(me, "balde");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                damage = damage_power(me, "blade");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           RED "ֻ��һ�ɽ�����$n" RED "���������ѱ�"
                                           "$P" RED "�⾫������һ"
                                           "�����У���Ѫ�ɽ�������\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "��$P" CYN "�������ڣ����ҵֵ�����æбԾ�ܿ���\n"NOR;
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
