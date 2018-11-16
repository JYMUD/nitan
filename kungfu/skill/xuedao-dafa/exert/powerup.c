#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int lv);

int exert(object me, object target)
{
        object weapon;
        int skill, lv;

        if (target != me)
                return notify_fail("��ֻ����Ѫ�����������Լ���ս������\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        lv = me->query_skill("xuedao-dafa", 1) / 3;

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "����һ��������ȫ��������죬����������ɱ"
                        "���������������ˡ�\n" NOR, me);

        if( objectp(weapon=query_temp("weapon", me)) && 
           query("skill_type", weapon) == "blade" && 
           me->query_skill_mapped("blade") == "xuedao-dafa")
        {
                message_combatd(HIR "$N" HIR "��Ŀ��Ц������" + weapon->name() +
                                HIR "��ʱ����һ��Ѫ�⣬�����ޱ�ɱ�⡣\n" NOR, me);
        }

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/damage", lv, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3, lv :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int lv)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                addn_temp("apply/damage", -lv, me);
                delete_temp("powerup", me);
                tell_object(me, "���Ѫ����������ϣ��������ջص��\n");
        }
}