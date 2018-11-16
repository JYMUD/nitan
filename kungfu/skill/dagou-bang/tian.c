// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "�����޹�" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;

        if( query("wugou", me)<500 )
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" + name() + "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("dagou-bang", 1) < 220)
                return notify_fail("��򹷰���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����" + weapon->name() + HIW "һ����"
              "���������������ǧ�ٸ����ƣ���������$n" HIW "����"
              "���С�\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        attack_time = 5;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ���ۻ����ң���������˷�������"
                       "Ӱ���ĵ׺���������м�ɢ�ҡ�\n" NOR;
                count = ap / 5;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 90);
        } else
        {
                msg += HIY "$n" HIY "ֻ����ǰһ������������˷�������"
                       "Ӱ����æ����������ϸ�мܡ�\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 12)
                attack_time = 12;

        addn("neili", -attack_time*30, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(4));

        return 1;
}
