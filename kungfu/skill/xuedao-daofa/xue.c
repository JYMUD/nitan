// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ѫ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 160)
                return notify_fail("���Ѫ���󷨻������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("��û�м���Ѫ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("qi", me)<100 )
                return notify_fail("��Ŀǰ��Ѫ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��Ŀǰ�������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "�ӵ������һ�գ�Ѫ���ʱ�������棬�������ұ�"
              "�ճ�һƬѪ����$n" HIR "��ͷ���䡣\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "ֻ��Ѫ����������ǰһ��Ѫ"
                                           "�죬����������£���Ѫ�ɽ�����������"
                                           "�󺿣�\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$n" CYN "������ã����Ų�æ�������$N"
                       CYN "�ı�ɱһ����\n"NOR;
                addn("neili", -100, me);
        }
        me->receive_wound("qi", 50);
        message_combatd(msg, me, target);
        return 1;
}
