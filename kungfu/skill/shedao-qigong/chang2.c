// ���ɷ�

#include <ansi.h>

string name() { return "���־�"; }
int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 80)
                return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

        if( query_temp("chang", me) <= -30 )
                return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");

        message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
                        "֮���������ǣ�\n" NOR, me);
        addn_temp("apply/attack", -10, me);
        addn_temp("apply/dodge", -10, me);
        addn_temp("apply/force", -10, me);
        addn_temp("apply/defense", -10, me);
        addn_temp("chang", -1, me);
        addn("neili", 1000, me);

        return 1;
}
