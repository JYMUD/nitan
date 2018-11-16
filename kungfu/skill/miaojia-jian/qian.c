#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "����ǧ��" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 160)
                return notify_fail("����ҽ���������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 220 )
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("��û�м�����ҽ���������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����" + weapon->name() + HIY "һ����������ʮ������"
              "�ҽ�����ʩ������$n" HIY "���ڽ���֮�С�\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "ֻ���ý����������ʱ��$P" HIR
                       "�����Ľ��й���Ӧ�Ӳ�Ͼ���������ˣ�\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 200);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "������ӿ����������"
                       "���˶��������Ҵ��⣬С��Ӧ����\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*25, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}