// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit F_SSERVER;

string name() { return "���Ŵ�"; }

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenmen-jian", 1);

        if( !(me->is_fighting() ))
                return notify_fail("���Ŵ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("�Է�û��ʹ�ñ��������������Ŵ�Ҳû�á�\n");

        if( skill < 160)
                return notify_fail("�������ʮ�����ȼ�����, �޷�ʩչ���Ŵ̡�\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷�ʩչ���Ẉ̂�\n");

        msg = HIY "ͻȻ$N" HIY "һ����ߣ�����" +weapon->name()+ NOR + HIY
                  "�й�ֱ����ֱ��$n���ŵ�" +weapon2->name()+ NOR + HIY"��"
                  "����\n" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if( ap / 2 + random(ap) > dp )
        {
                addn("neili", -120, me);
                msg = HIR "$nֻ������һ���ʹ������" +weapon2->name()+ NOR + HIR
                      "��Ҳ׽�ò�ס�����ֶ��ɣ�\n" NOR;
                me->start_busy(1 + random(2));
                if (! target->is_busy())
                        target->start_busy(2);
                weapon2->move(environment(target));
        }
        else
        {
                addn("neili", -40, me);
                msg = CYN "����$n������$N����ͼ�������б��л�����ܲ�͸�磬������$N" CYN
                      "�ı�����\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}