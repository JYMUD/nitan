// kuihua-xinfa (protect)
#include <ansi.h>
void remove_effect(object me, int amount);
int exert(object me, object target)
{
    int skill;
    if( target != me ) 
        return notify_fail("�����ķ�ֻ�ܶ��Լ�ʹ�á�\n");
    if( query("neili", me)<1000 )
        return notify_fail("�������������\n");
    if( query_temp("apply/shade_vision", me) )
        return notify_fail("���Ѿ����˹����ˡ�\n");
    skill = me->query_skill("kuihua-xinfa",1);
        if (skill<90) return notify_fail("��Ŀ����ķ���������졣\n");
    message_vision( HIW "$N΢һ������������ķ�����������ͬ����������һ�㣬Ư��������\n"
    "����������\n" NOR, me);
    addn("neili", -300, me);
    set_temp("apply/shade_vision", 1, me);
me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/200);
if ((int)me->query_skill("kuihua-xinfa", 1)<450)
    me->improve_skill("kuihua-xinfa", random(me->query_skill("kuihua-xinfa", 1)/10),0);
    if( me->is_fighting() ) me->start_busy(1);
    return 1;
}
void remove_effect(object me, int amount)
{
    if (!me)    return;
    delete_temp("apply/shade_vision", me);
    message_vision( BOLD "$N�Ŀ����ķ�������ϣ�ȫ�����һ�٣��ֳ��������Ρ�\n" NOR, me);
}
void reset() { }
int clean_up() { return 1; }


