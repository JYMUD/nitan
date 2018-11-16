#include <ansi.h>

inherit F_SSERVER;

string name() { return "������"; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query_temp("weapon", me) )
                return notify_fail("�����ϲ���װ���κζ�����\n");

        if (! me->is_fighting(target))
                return notify_fail("ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 100 )
                return notify_fail("��ġ���������������죬����ʹ�á������㡹��\n");

        if( (int)me->query_skill("biyun-xinfa",1) < 100)
                return notify_fail("����ķ�����������\n");

        if( query("neili", me)<800 )
                return notify_fail("�������������\n");

        ap = attack_power(me, "hand") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        msg = HIG "$N����һ��������һ���黨�����������£����͡���һ�����ƿն�ȥ!\n"NOR;

        message_combatd(msg, me, target);

        addn("neili", -500, me);

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(ap/100 +2);
                msg = HIC "$nȫ��پ�һ�飬�ƺ����ܶ�����\n"NOR;
        }
        else
                msg = HIM "ֻ��$n����һ�ã�һ��������ƿն�����\n"NOR;
        message_combatd(msg, me, target);

        return 1;
}
