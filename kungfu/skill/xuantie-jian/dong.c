#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "�󽭶�ȥ" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string wp, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 200)
                return notify_fail("�����������������죬����ʩչ" + name() + "��\n");

        /*
        if ((int)weapon->query_weight() < 25000)
                return notify_fail("�����е�" + wp + "��������������ʩչ" + name() + "��\n");
        */

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�������񣬶�ʱһ��������������ȱŷ������ŵ�"
              "��һ������" + wp + HIW "\n�漴��վ����������Χ��ɳ����"
              "����ʩ��������������" HIG "�󽭶�ȥ" HIW "����\n"NOR;

        me->start_busy(2);

        ap = attack_power(me, "sword") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_str()*10;

        if( query("character", me) == "��������" || query("character", me) == "������˫" )
                ap += ap / 5;

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -600, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "���$n" HIR "�����мܣ�ȴ��$N" HIR
                                           "��һ����ķ��𣬿�����Ѫ���²�ֹ��\n" NOR);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ����æбԾ�ܿ���\n"NOR;
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}