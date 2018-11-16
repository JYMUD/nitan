// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;
        
        extra = me->query_skill("jinshe-jian",1);
        time = extra/40; 
        
        if( !target ) target = offensive_target(me);
        
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�����������ֻ����ս����ʹ�á�\n");
                
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                        return notify_fail("��ʹ�õ��������ԡ�\n");
                        
        if( query("id", weapon) != "jinshejian" )
                return notify_fail("û�н��߽�������ʹ�����߽����Ķ�����ʽ�������������\n");
                
        if((int)me->query_skill("sword") <200)
                return notify_fail("��Ľ�����Ϊ������ Ŀǰ����ʹ�á����������! \n");
                
        weapon=query_temp("weapon", me);
        if( query("neili", me)<1000 )
                return notify_fail("�������������\n");
                
        msg = HIR  "$N����һ����������������ʢ�����е�"+ weapon->name()+  HIR"���ٻ��裬������������$n������" NOR;
        message_combatd(msg,me,target);
        addn_temp("apply/attack", extra/5, me);
        addn_temp("apply/damage", extra/5, me);
        for(i=1;i<=(int)time;i++)
        {
                // msg =  YEL "$N���к������ģ�������������ӵ���߾��磡\n" NOR;
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR);
        }
        addn_temp("apply/attack", -extra/5, me);
        addn_temp("apply/damage", -extra/5, me);
        addn("neili", -500, me);
        me->start_busy(3);
        return 1;
}
