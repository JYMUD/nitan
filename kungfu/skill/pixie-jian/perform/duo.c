#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ӱ��Ŀ" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int lvl, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("pixie-jian", 1) < 80)
                return notify_fail("��ı�а����������죬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ" + name() + "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( query_temp("block_msg/all", target) )
                return notify_fail("�Է�����ʲôҲ���������ŵ������ɡ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
        {
                msg = HIR "$N" HIR "һ����Ц��������ϣ�������ָ��£���ֱ�"
                      "������Ѹ���쳣�ִ�$n" HIR "��˫Ŀ��\n" NOR;
        } else
        {
                msg = HIR "$N" HIR "һ����Ц��������ϣ�����" + weapon->name() +
                      HIR "һ�񣬽���һ�㱩�����ִ�$n" HIR "����˫Ŀ��\n" NOR;
        }

        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap*2) > dp)
        {
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                          (: final, me, target, me->query_skill("pixie-jian", 1) :));
                me->start_busy(2);
                addn("neili", -80, me);
                message_combatd(msg, me, target);
                set_temp("block_msg/all", 1, target);
        } else
        {
                msg += CYN "$n" CYN "�鼱������̧��Ҳ��$N"
                       CYN "�����۴�ȥ���ȵ�$P" CYN "�ؽ�Ծ����\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
                message_combatd(msg, me, target);
        }
        return 1;
}

string final(object me, object target, int ap)
{
        target->start_call_out((: call_other, __FILE__, "cimu_end", me, target :), 5 + random(ap / 100));
        return HIR "$n" HIR "ֻ��˫Ŀһ���ʹ����ǰһ�ڣ���ʲô"
               "Ҳ�������ˣ���ʱ����ʹ��������\n" NOR;
}

void cimu_end(object me, object target)
{
        if (! objectp(target)) return;
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "Ĩ��Ĩ���ŵ�"
                                        HIR "��Ѫ" HIC "�������ܿ�"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIR "������Ĩ������ǰ��"
                                            "��Ѫ���ܿ����ˡ�\n" NOR);
                        set_temp("block_msg/all", 0, target);
                }
        }
        return;
}
