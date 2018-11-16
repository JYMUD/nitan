// This program is a part of NITAN MudLIB
// recover.c ��Ԫ��
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "��Ԫ��" NOR; }

int perform(object me, string skill)
{
        mapping my;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
            
        if( time()-query("special/recover", me)<1440 )
                return notify_fail("��Ԫ��һ��ֻ��ʩչһ�Σ�\n");

        message_vision(HIC "$N" HIC "ʩչ����Ԫ�󷨣�����ͻ���澭�������ָ�����״̬��\n" NOR, me);
       
        set("special/recover", time(), me);
        
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();

        me->clear_condition();

        return 1;
}

