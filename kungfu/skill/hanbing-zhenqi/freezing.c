#include <ansi.h>
inherit F_CLEAN_UP;

#define FRE "��" HIW "��������" NOR "��"

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( userp(me) && !query("can_perform/hanbing-zhenqi/freezing", me) )
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if( query_temp("freezing", me) )
                return notify_fail("����������ʩչ" FRE "��\n");

        if (target != me)
                return notify_fail(FRE "ֻ�ܶ��Լ�ʹ�á�\n");

        skill = me->query_skill("hanbing-zhenqi", 1);

        if( query("con", me)<34 )
                return notify_fail("���������ǲ��㣬�޷�ʩչ" FRE "��\n");

        if (skill < 140)
                return notify_fail("��ĺ�����������������ʩչ" FRE "��\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("���������Ϊ���㣬����ʩչ" FRE "��\n");

        if( !query_temp("powerup", me) )
                return notify_fail("��������δ���˹�������ʩչ" FRE "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("��Ŀǰ����������������ʩչ" FRE "��\n");

        addn("neili", -300, me);

        message_combatd(HIW "$N" HIW "һ����Ц�����ں�������Ѹ�ټ�ת������"
                        "�죬�����������ġ�\n" NOR, me);
        set_temp("freezing", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("freezing", me) )
        {
                delete_temp("freezing", me);
                tell_object(me, "���" FRE "������ϣ��������ջص��\n");
        }
}