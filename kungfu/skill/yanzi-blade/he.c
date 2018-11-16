// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "˫���ϱ�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon1, weapon2;
        int i, count, damage;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon1=query_temp("weapon", me);
        weapon2=query_temp("secondary_weapon", me);
        if( !objectp(weapon2) )
        weapon2=query_temp("handing", me);

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ��˫��������ʩչ" + name() + "��\n");

        if( query("consistence", weapon2) <= 0 )
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");

        if( query("skill_type", weapon1) != query("skill_type", weapon2) ||
            query("skill_type", weapon1) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        type=query("skill_type", weapon1);

        if (me->query_skill(type, 1) < 250)
                return notify_fail("���" + to_chinese(type) + "̫�"
                                   "����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped(type) != "yanzi-blade")
                return notify_fail("��û�м�������˫�ɵ���������ʩչ" + name() + "��\n");

        if (me->query_skill("yanzi-blade", 1) < 250)
                return notify_fail("�������˫�ɵ����ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�ֳ����ѵ�������$n " HIW "����������һɲ�Ǽ䣬���ѵ��·��Ȼ�����һ�ѵ���\n"
              HIW "˫���ϱڣ�������������һ����������һǧ���������������Ϊ��ǧ�����������һ�����ٶȵ�ȻҲҪ����һ����\n"
              HIW "$N" HIW "˫���ϱڣ����ѵ������Ѻ϶�Ϊһ��ȴ��ƫƫ�·��Ǵ�������ͬ�ķ����������ġ�\n"
              HIW "�����ǿ���$n" HIW "���ұߣ�����$n" HIW "�������ܣ�������������$n" HIW "������������������\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                damage = damage_power(me, "blade") * 2;
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "ֻ��$n" HIR "һ���ҽУ��ؿڸ�"
                                           "����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
