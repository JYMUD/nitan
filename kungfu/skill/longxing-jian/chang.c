// ��������

#include <ansi.h>

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("���γ���ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("�����������Ԫ��������죬����ʹ�����γ��ɡ�\n");

        if( query("neili", me)<300 )
                return notify_fail("���Ѿ���ƣ���ߣ����������ˡ�\n");

        if( query_temp("chang", me) >= 100 )
                return notify_fail("���Ѿ��е�̫���ˣ������Ѿ�����ˡ�\n");

        addn("neili", -100, me);

        message_combatd(HIR "ֻ��$N" HIR "���������дʣ��������������"
                        "����$N���У�\n" NOR, me);

        addn_temp("apply/attack", 1, me);
        addn_temp("apply/dodge", 1, me);
        addn_temp("apply/defense", 1, me);
                addn_temp("apply/armor", 1, me);
                addn_temp("apply/damage", 1, me);
        addn_temp("chang", 1, me);

        return 1;
}
