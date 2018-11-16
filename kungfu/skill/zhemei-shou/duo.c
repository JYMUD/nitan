// This program is a part of NITAN MudLIB
// duo.c ���������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���������"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int ap, dp, skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("zhemei-shou", 1);

        if (! me->is_fighting())
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("�������֡�\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("�Է�û�б��У��㲻�õ��ġ�\n");

        if (skill < 50)
                return notify_fail("�����ɽ��÷�ֵȼ�����, ���ܿ�������У�\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 50 &&
            (int)me->query_skill("xiaowuxiang", 1) < 80 &&
            (int)me->query_skill("beiming-shengong", 1) < 50)
                return notify_fail(RED"�㱾���ڹ���򲻹���ʹ���������ֶ���С���\n"NOR);

        if( query("neili", me)<100 )
                return notify_fail("��������������޷���������У�\n");

        msg = CYN "$N�����Ϣ������ʩչ��������еľ���. \n";
        message_combatd(msg, me, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg = "$Nʹ����������еľ���, $n��ʱ������ǰһ��������һ�飬���б������ֶ�����\n" NOR;
                weapon2->move(me);
                if (weapon2->is_item_make() && random(2))
                {
                        weapon2->move(target);
                        msg += "�ǿ���$n������һ$n��һ�콫���������\n" NOR;
                }
                me->start_busy(2);
        }
        else
        {
                msg = "����$p�Ŀ�����$P����ͼ�����̲�ȡ���ƣ�ʹ$Pû�ܶ��±��С�\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}