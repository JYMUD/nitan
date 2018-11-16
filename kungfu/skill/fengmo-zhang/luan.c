// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "Ⱥħ����" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ"+name()+"��\n");

        if ((lvl = (int)me->query_skill("fengmo-zhang", 1)) < 120)
                return notify_fail("���ħ�ȷ���򲻹�������ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("staff") != "fengmo-zhang")
                return notify_fail("��û�м�����ħ�ȷ�������ʩչ"+name()+"��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ"+name()+"��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "����ɱ����ʢ������һ����������ǰ��"
                  "���緢��һ�㣬���е�" + weapon->name() +
              HIR "����������Ӱ��һ�����$n" HIR "��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {

                msg += HIY "$n" HIY "��$N" HIY "������ƣ�����������"
                       "ս��һʱ��֪Ӧ����εֵ���Ψ���������ˡ�\n" NOR;
                count = lvl / 10;
                addn_temp("apply/attack", count, me);
        } else
                count = 0;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(5));
        return 1;
}