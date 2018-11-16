// This program is a part of NITAN MudLIB
// demon.c ��ħ����
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "��ħ����" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int n;

        if( query_temp("special_skill/demon", me) )
                return notify_fail("����ħ����֮������ʩչ���ˡ�\n");

        message_vision(HIG "$N" HIG "ʩչ����ħ����֮����ɲ�Ǽ�ȫ�������ŷ�������������֣������ޱȣ�\n" NOR, me);

        n = me->query_skill("force");
        if (n < 100) n = 100;

        addn_temp("apply/armor", n*3, me);
        addn_temp("apply/reduce_damage", 30, me);
        set_temp("special_skill/demon", 1, me);
 
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, n * 3 :), n/10);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("special_skill/demon", me) )
        {
                addn_temp("apply/armor", -amount, me);
                addn_temp("apply/reduce_damage", -30, me);
                delete_temp("special_skill/demon", me);
                tell_object(me, "����ħ����֮����ʩչ��ϡ�\n");
        }
        
}

