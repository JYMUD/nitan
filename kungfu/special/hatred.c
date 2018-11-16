// hatred.c ɱ��
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "ɱ������" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("���������֧���޷����������Լ����˺�����\n");

        if( query_temp("special_skill/hatred", me) )
                return notify_fail("�������Ѿ���ɱ�������ˡ�\n");

        message_vision(HIR "$N" HIR "���о��������������ɨ��"
                       "���ܣ�һ�ɺ�����Ȼ����\n" NOR, me);
        switch(query("character", me) )
        {
        case "��������":
                count = 30;
                break;

        case "�ĺ�����":
                count = 42;
                break;

        case "������":
                count = 38;
                break;

        case "���ռ�թ":
                count = 48;
                break;

        case "��ʿ��˫":
                count = 60;
                break;

        }

        count *= me->query_str();
        set_temp("special_skill/hatred", 1, me);
        me->receive_damage("qi", 40 + random(40));
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_damage", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/hatred", me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        tell_object(me, "�㾫��һ��и��ɱ����Ȼ�޴档\n");
}
