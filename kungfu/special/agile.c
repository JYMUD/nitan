// agile.c �������
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "�������" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("���������֧���޷����������Լ����ٶȡ�\n");

        message_vision(HIC "$N" HIC "�ż�һ�㣬����һЩ��"
                       "���������˶�ʱ��ֽͬ��һ��ƮƮ������\n" NOR, me);
        count = me->query_dex();

        if( query_temp("special_skill/agile", me) )
                return notify_fail("���Ѿ������������Լ����ٶ��ˡ�\n");

        me->receive_damage("qi", 40 + random(40));
        set_temp("special_skill/agile", 1, me);
        addn_temp("apply/dodge", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/agile", me);
        addn_temp("apply/dodge", -count, me);
        tell_object(me, "����������ʩչ��ϣ�����һ�٣�������������\n");
}
