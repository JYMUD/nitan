// This program is a part of NITAN MudLIB
// stealth.c ��������
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIK "��������" NOR; }

int perform(object me, string skill)
{
        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
            
        if( time()-query("special/stealth", me)<21600 )
                return notify_fail("��Ҫ��Щʱ��������ô˼��ܣ�\n");

        message_vision(HIK "$N" HIK "ʩչ���������٣���ӰԽ��Խ���������������ˡ�\n" NOR, me);

        set_temp("apply/shade_vision", 1, me);
        set("special/stealth", time(), me);
        if( me->is_fighting() && me->is_busy() ) {
                me->remove_all_killer(); 
                all_inventory(environment(me))->remove_killer(me); 
                me->stop_busy();
        }
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        delete_temp("apply/shade_vision", me);
        tell_object(me, "��ʩչ���������٣�����һ������\n");
        message_vision(HIK "$N" HIK "����������¶��������������ɼ���\n" NOR, me);
}
