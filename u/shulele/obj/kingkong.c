// This program is a part of NITAN MudLIB
// kingkong.c �������
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "�������" NOR; }

int perform(object me, string skill)
{
        object target;
        string msg;
        int ap, dp;

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

        if( !query_temp("special_skill/immortal", target) )
                return notify_fail("�Է���û������������ѽ ��\n");
       
        message_vision( HIR "$N" HIR "��ɫͻȻ��ó�죬˫�ֹ���޴�������"
                        HIR "����һ��Ϯ��$n��\n\n" NOR, me, target);

        ap = me->query_str(); 
        dp = target->query_con();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("special_skill/immortal", target);
                message_vision( CYN "ֻ��$n" CYN "�ƺ�һ����"
                                CYN "����������$N" CYN "������\n\n" NOR, me, target );

                tell_object( target, HIW "��Ĳ�������" NOR + me->name() +
                                    HIW "�Ƴ��ˣ�\n\n" NOR );           
        } else 
                message_vision( HIY "ֻ��$n" HIY "Ӳ��������$N" HIY "��һ�У�"
                                HIY "��������˿����Ϊ������\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

