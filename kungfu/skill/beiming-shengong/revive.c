// This program is a part of NITAN MudLIB
// revive.c

// ��������������ƣ�����ϱ��������Ǻ����̹�����������֮�����������ս�ǰ��
// ������ָ�������ѷ������Ů�Ӷϱ۴���Ѩ����Ѫ����ֹ�������ε�ָʱ��ʹ��
// ��ͯ�����̵�һ�С�������������һ�ɵı�ڤ�����������ı۸����и�Ѩ���С���Ů
// �ӡ�������һ����У�����ת����

#include <ansi.h>

int exert(object me, object target)
{       
        if( !target )           
                return notify_fail("���Լ������ѵ���\n");     

        if( me->is_fighting() || target->is_fighting())         
                return notify_fail("ս�����޷��˹���\n");       

        if(target == me)                
                return notify_fail("�㲻�ܶ��Լ��˹���\n");     

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ������\n");     

        if( query("neili", me)<350 )
                return notify_fail("�������������\n");        

        if( living(target) )            
                return notify_fail( target->name() +"�Ѿ������ѵģ�\n");        

        message_vision(HIY "$N������ָ������һ�С�������������һ����������$n�ı۸����и�Ѩ���С�\n\n" NOR,me, target );    

        target->revive(); 
        
        addn("neili", -250, me);
        set("jiali", 0, me);
        me->start_busy(2);                
        target->start_busy(2);  

        return 1;
}