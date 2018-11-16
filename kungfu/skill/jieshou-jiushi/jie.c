#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "�ؽ����" NOR; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jieshou-jiushi", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (skill < 100)
                return notify_fail("��Ľ��־�ʽ�ȼ�����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hand") != "jieshou-jiushi")
                return notify_fail("��û�м������־�ʽ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") != "jieshou-jiushi")
                return notify_fail("������û��׼��ʹ�ý��־�ʽ������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һչ����ȻԾ��$n" HIR "��ǰ��ʮָ���ţ�ֱ��$n"
              HIR "ҪѨ�����ǽ��־�ʽ�������ؽ��������\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                me->start_busy(3);

                damage = damage_power(me, "hand");

                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                target->receive_damage("qi", damage * 3 / 2);
                target->receive_wound("qi", damage * 3 / 2);
                if( !target->is_busy() )
                        target->start_busy(1);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
                       damage, 10, HIR "$n" HIR "�����񵲣��ɻ��Ǳ�$N"
                                   HIR "��ס��ҪѨ��ֻ����ǰһ�ڣ�"
                                   "�����ε���\n" NOR);
        }
        else
        {
                addn("neili", -100, me);
                msg += CYN "$n" CYN "��״���һ������æ�������������"
                       "���ڱܿ���$N" CYN "��һ����\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
