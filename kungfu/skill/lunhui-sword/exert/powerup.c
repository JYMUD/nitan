#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���������ֻؽ��������Լ���ս������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        message_combatd(HIG "\n$N" HIG "��̾һ�������챦����̸Ц�����䣬�������������ڶ�����ӿ����ʣ�����һ���������ʧ�ˡ�\n" NOR, me);

        // ��ͨBREAKUP���Ч������20%
        if( query("breakup", me))skill=skill+skill*2/10;

        addn_temp("apply/attack", skill, me);
        addn_temp("apply/damage", skill, me);

        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 2);
      
        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;
                                
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/damage", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, HIY "��������ֻؽ�������ͨ�졹������ϣ��������ջص��\n" NOR);
        }


}