// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me) 
                return notify_fail("��ֻ���û��������������Լ���ս������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");
                
        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(
                HIR "$N΢һ�����������������ȫ��ǽڷ���һ�󱬶�������좦\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :),  skill);

        if (me->is_fighting() && ! me->is_busy()) 
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, HIY "��Ļ�������������ϣ��������ջص��\n" NOR);
        }
}
