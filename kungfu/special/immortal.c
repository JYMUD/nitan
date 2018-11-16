// This program is a part of NITAN MudLIB
// immortal.c ��������
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "��������" NOR; }

int perform(object me, string skill)
{
        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
            
        if( time()-query("special/immortal", me)<3600 )
                return notify_fail("��Ҫ��Щʱ��������ô˼��ܣ�\n");

        message_vision(YEL "$N" YEL "��ɫһ����ȫ��ɢ����һ���⣬"
                       YEL "�����޺�ת��һ�㡣\n" NOR, me);

        set_temp("special_skill/immortal", 1, me);
        set("special/immortal", time(), me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        delete_temp("special_skill/immortal", me);
        tell_object(me, "��ʩչ�겻����������һ������\n");
}
