// This program is a part of NITAN MudLIB
// six.c ��������

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "��������" NOR; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i, ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" + name() + "��\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 220)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" + name() + "��\n");

        if (me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת��"
                                   "���γ�" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("������������������޷�ʩչ" + name() + "��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ" + name() + "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "̯��˫�֣���ָ��������ʱ��������ȣ���"
              "�����ڣ���������������Ѩ��һ��ɱ��$n" HIY "��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                delta = skill / 2;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ�����������˺���ǿ��\n"NOR;
                        delta += delta * n * 15 / 100;
                }
                msg += HIR "$n" HIR "���˽����ݺᣬ΢һ��񣬲����������⡣\n" NOR;
        } else
                delta = 0;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", delta, me);
        addn_temp("apply/defense", delta, me);
        addn_temp("apply/unarmed_damage", delta, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                set_temp("six-finger/hit_msg", i, me);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -delta, me);
        addn_temp("apply/defense", -delta, me);
        addn_temp("apply/unarmed_damage", -delta, me);
        delete_temp("six-finger/hit_msg", me);
        me->start_busy(1 + random(3));

        return 1;
}
