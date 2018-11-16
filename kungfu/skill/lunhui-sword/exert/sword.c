
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        object weapon;

        if (target != me)
                return notify_fail("��ֻ���������ֻؽ��������Լ���ս������\n");

        if( query_temp("sword", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("�㻹û�м��������ֻؽ�Ϊ�������޷��˹���\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("�㻹û��װ������ı������޷��˹���\n");
                
        skill = me->query_skill("force");
        
        if( query("neili", me)<3000 )
                return notify_fail("���������㣬�޷��˹���\n");
                
        addn("neiil", -3000, me);
        
        message_combatd(NOR + CYN "$N��ת����" + weapon->name() + NOR + CYN "����̼䣬ֻ��" + weapon->name() + 
                        NOR + CYN "��һ�����²�������â�����֣��������죡\n\n" NOR, me);

        // ��ͨBREAKUP���Ч������20%
        if( query("breakup", me))skill=skill+skill*2/10;

        addn_temp("apply/damage", skill/4, me);
        addn_temp("apply/sword", skill/8, me);
        set_temp("sword", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 10);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;

        if( query_temp("sword", me) )
        {
                addn_temp("apply/damage", -amount/4, me);
                addn_temp("apply/sword", -amount/8, me);

                delete_temp("sword", me);
                tell_object(me, HIW "��������ֻؽ����ֻؽ�����������ϣ��������ջص��\n" NOR);
        }


}