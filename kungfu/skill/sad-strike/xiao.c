// xiao.c ��Ȼ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "��Ȼ����" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("sad-strike", 1) < 150)
                return notify_fail("�����Ȼ�����ƻ�򲻹����޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 320)
                return notify_fail("����ڹ���Ϊ�������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "sad-strike")
                return notify_fail("������û��׼��ʹ����Ȼ�����ƣ��޷�ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n$N" HIM "һ������������Ȼ�����ߣ�Ψ������ӣ�������ʱ����"
              "ֹˮ����Ȼ���ˣ�\n�ڲ�����������ʹ����" HIR "����Ȼ���꡻" HIM "��\n" NOR;

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIY "$n" HIY "��$P" HIY "��һ�б仯Ī�⣬�����"
                       "�������ɴ��һ��������������������\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����С��$P" HIC
                       "�����У���Ų������С���мܡ�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -400, me);
        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(5));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}
