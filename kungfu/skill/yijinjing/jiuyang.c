// This program is a part of NT MudLIB
// jiuyang.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( !query("can_exert/yijinjing/jiuyang", me) )
                return notify_fail("�㻹û����������־��������أ�\n");

        if ((int)me->query_skill("yijinjing", 1) < 140)
                return notify_fail("����׽��Ϊ���֮ǳ�������þ���������\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ̫��������ɡ�\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        if( query_temp("sl/jiuyang", me) )
                return notify_fail("���Ѿ������������ӹ�������\n");

        skill = me->query_skill("yijinjing",1);
        message_combatd(HIR"\n$NǱ�����־����񹦣������������Ȳ�Ϣ��ȫ��������������ׯ�ϣ�\n" NOR, me);

        addn_temp("apply/attack", skill, me);
        set_temp("sl/jiuyang", 1, me);
        addn("neili", -300, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill*2);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
void remove_effect(object me, int amount)
{
        if( query_temp("sl/jiuyang", me)){
                addn_temp("apply/attack", -amount, me);
                delete_temp("sl/jiuyang", me);
                message_vision(HIY"$N�����������ջص����¶����Ц�ݡ�\n" NOR, me);
        }
}