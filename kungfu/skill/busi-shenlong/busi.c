// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me ) return notify_fail("��ֻ���ò��������������Լ���ս������\n");

        if( (int)me->query_skill("busi-shenlong",1) < 50 )
          return notify_fail("����ڹ���򻹲������޷�ʹ�ò��������󷨣�\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������!\n");
        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);

        message_combatd(
          HIR "$N˫Ŀ��죬����������������ͨ���ӣ��ڵ��������ٱ�����һ���٣��԰ٵ���\n"NOR, me);
        tell_object(me,HIW"���ʱ�о��书�������������ǰ����������\n" NOR);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "��Ĳ���������������ϣ�����Ȫӿ������������\n");
        }
}