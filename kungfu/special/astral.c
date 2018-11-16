// This program is a part of NITAN MudLIB
// astral.c ������ͫ
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIW "������ͫ" NOR; }

int perform(object me, string skill)
{
        string msg;
        int ap, dp;
        object target;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");

        if( !target ) { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        } 

        if( !target || !target->is_character() 
         || query("not_living", target) )
                return notify_fail("������˭ʩչ" + name() + "��\n");
                
        if( !me->is_fighting(target) ) 
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");      

        if( !query_temp("apply/shade_vision", target) )
                return notify_fail("�Է���û����������ѽ ��\n");
       
        message_vision( HIR "$N" HIR "ʩչ��������֮ͫ����������â����$n" 
                        HIR "������\n\n" NOR, me, target);

        ap = me->query_int(); 
        dp = target->query_dex();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("apply/shade_vision", target);
                message_vision( CYN "ֻ��$n" CYN "�ƺ�һ��������â���У���ʱ�޷�����\n\n" NOR, 
                                me, target );

                tell_object( target, HIW "�������" NOR + me->name() + HIW "�Ƴ��ˣ�\n\n" NOR );           
        } else 
                message_vision( HIY "ֻ��$n" HIY "���������$N" HIY "����â��"
                                HIY "����״̬˿��û���ܵ�Ӱ�죡\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

