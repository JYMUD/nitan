// This program is a part of NITAN MudLIB
// sneaky.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        
        if( userp(me) && !query("reborn/times", me) )
                return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�\n");
                
        if (target != me)
                return notify_fail("��а����ֻ�ܶ��Լ�ʹ�á�\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if (me->query_skill("pixie-jian", 1) < 120)
                return notify_fail("��ı�а�������в����������˹���\n");

        if( query_temp("apply/shade_vision", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        
        message_combatd( HIW "$N" HIW "΢һ��������������������ͬ����������һ�㣬Ư������������������\n" NOR, me);

        set_temp("apply/shade_vision", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int level)
{
        if( query_temp("apply/shade_vision", me) )
        {
                delete_temp("apply/shade_vision", me);
                message_vision(HIW "$N" HIW "�˹���ϣ�ȫ�����һ�٣��ֳ��������Ρ�\n" NOR, me);
        }
}
