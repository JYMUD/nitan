// ���ɷ�

#include <ansi.h>

string name() { return "���־�"; }

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 60)
                return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

        if( query("neili", me)<300 )
                return notify_fail("���Ѿ����þ�ƣ���ߣ����������ˡ�\n");

        if( query_temp("chang", me) >= 30 )
                return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);

        message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
                        "֮���书�����\n" NOR, me);

        addn_temp("apply/attack", 10, me);
        addn_temp("apply/dodge", 10, me);
        addn_temp("apply/force", 10, me);
        addn_temp("apply/defense", 10, me);
        addn_temp("chang", 1, me);

        return 1;
}