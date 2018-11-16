// richu.c ���¹⻪ ֮ �ճ�����
// By haiyan

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

        if( query("gender", me) != "����" && !query("reborn/times", me))
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

    if (target != me)
        return notify_fail("��ֻ�������¹⻪�������Լ���Ǳ����\n");

    if ((int)me->query_skill("riyue-guanghua",1) < 100)
        return notify_fail("������¹⻪��Ϊ̫�ͣ��޷�ʩչ���ճ���������\n");

    if( query("neili", me)<200 )
        return notify_fail("�������������\n");

    if( query_temp("richu", me) )
        return notify_fail("���Ѿ����˹����ˡ�\n");

    skill = me->query_skill("force");
    addn("neili", -120, me);
    me->receive_damage("qi", 0);
    message_combatd(HIR "$N" HIR "һ����Х��˫Ŀ��ó�죬˫��һ�㣬�����ڿն���"
                    "���ܶ�ʱ���˷�ӿ�������ѵ���\n" NOR, me);
    addn_temp("apply/attack", skill/3, me);
    addn_temp("apply/dodge", skill/3, me);
    addn_temp("apply/parry", skill/3, me);
    addn_temp("apply/damage", skill*3, me);
    addn_temp("apply/dex", skill/20, me);

    set_temp("richu", 1, me);

    me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                         skill:), skill);
    if (me->is_fighting()) me->start_busy(3);

    return 1;
}

void remove_effect(object me, int amount)
{
    if( query_temp("richu", me) )
    {
        addn_temp("apply/attack", -amount/3, me);
        addn_temp("apply/dodge", -amount/3, me);
        addn_temp("apply/parry", -amount/3, me);
        addn_temp("apply/damage", -amount*3, me);
        addn_temp("apply/dex", -amount/20, me);
        delete_temp("richu", me);
        tell_object(me, "����ճ�����������ϣ��������ջص��\n");
    }
}
