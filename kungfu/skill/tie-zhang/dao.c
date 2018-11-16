#include <ansi.h>
#include <combat.h>

string name() { return HIR "��ָ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tie-zhang", 1) < 180)
                return notify_fail("�������Ʒ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("��û��׼�������Ʒ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2800 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<400 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "����һչ��ʩ�����ƾ�����" HIR "��ָ��" NOR +
              WHT "�����Ʒ漤�������ˣ���$n" WHT "������ȥ��\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*10;
        dp=defense_power(target,"parry")+target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "���$N" HIR "����ɽ������Ĺ�"
                       "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ"
                       "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -250, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/2, me);
        return 1;
}
