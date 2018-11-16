// powerup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me ) return notify_fail("��ֻ�������Լ���ս������\n");
        if( query("neili", me)<100)return notify_fail("�������������\n");
        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        message_combatd(HIR"$N���һҧ�����һ����Ѫ����������������ѽ�ȫ��Ǳ����������\n" NOR, me);

        addn_temp("apply/attack", skill, me);
//        me->addn_temp("apply/dodge", skill);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
//                me->addn_temp("apply/dodge", - amount);
                delete_temp("powerup", me);
                tell_object(me, "��ľ���������������ϣ��������ջص��\n");
        }
}