// heal.c

#include <ansi.h>

int exert(object me, object target, int amount)
{
        if( me->is_fighting() )
                return notify_fail("ս�����˹����ˣ�������\n");

        if( query("neili", me)-query("max_neili", me)<50 )
                return notify_fail("�������������\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return 
notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        write( HIW "��ȫ����ɣ���������ʼ�˹����ˡ�\n" NOR);
        message("vision",
                HIW + me->name() + 
"�������˹����ˣ�����һ���һ��ף����ã��³�һ����Ѫ����ɫ�������ö��ˡ�\n" 
NOR,
                environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
        addn("neili", -50, me);
        set("force_factor", 0, me);
        me->start_busy(2);
        return 1;
}
 