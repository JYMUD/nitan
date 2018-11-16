// power.c ������
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "������" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("���������֧���޷�Ѹ�������Լ���ս������\n");

        message_vision(HIY "$N" HIY "˫��һ��һ����ϥ��΢�䣬"
                       "�������ˡ�\n" NOR, me);
        count = me->query_str();

        if( query_temp("special_skill/power", me) )
                return notify_fail("���Ѿ����������Լ���ս�����ˡ�\n");

        me->receive_damage("qi", 40 + random(40));
        set_temp("special_skill/power", 1, me);
        addn_temp("apply/attack", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/power", me);
        addn_temp("apply/attack", -count, me);
        tell_object(me, "��ʩչ��������������һ������\n");
}
