// recover.c
//inherit SSERVER;
int exert(object me, object target)
{
        int n, q;
    
        if (me != target)
                return notify_fail("��ֻ�����ڹ��ָ��Լ��ľ�����\n");
        
        if( query("neili", me)<20 )
                return notify_fail("�������������\n");
        
        q=query("max_jingli", me)-query("jingli", me);
        if (q < 10)
                return notify_fail("�����ھ������档\n");
    
        n = 100 * q / me->query_skill("force");
        n = 100 * n / me->query_con();
        if (n < 20)
                n = 20;
        if( query("neili", me)<n){
                q=q*query("neili", me)/n;
                n=query("neili", me);
        }
        addn("neili", -n, me);
        addn("jingli", q, me);
        if( query("jingli", me)>query("max_jingli", me) )
        set("jingli",query("max_jingli",  me), me);
    
        message_vision("$N�������˼��������о����ֳ����˻�����\n", me);
        if (me->is_fighting()) me->start_busy(2);
        return 1;
}