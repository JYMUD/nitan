// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int di);

int exert(object me, object target)
{
        int skill;
        int di;
        object weapon;

        if (target != me)
                return notify_fail("��ֻ�����ټ�ׯ�����Լ���ս������\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("�������������\n");

        if ((int)query_temp("powerup", me))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        if (query("sex", me)) di = 0; else di = skill / 2;
        if (di > 1000) di = 1000;

        message_combatd(MAG "$N" MAG "΢һ���������ټ�ׯ��һ�����ȣ�"
                        "���ܵĿ����·������ˣ�\n" NOR, me);

        if (objectp(weapon = query_temp("weapon", me)))
        {
                if (di >= 95)
                        message_combatd(HIR "$N" HIR "��ɫһ���������ټ�ׯ��ͨ����ʱ��" +
                                        weapon->name() + HIR "�⻪���䣬�����ޱ�ɱ�⡣\n" NOR, me);
                else
                if (di >= 80)
                        message_combatd(HIR "$N" HIR "Ǳ��������ֻ��" +
                                        weapon->name() + HIR "����һ���⻪���������ˣ��������¡�\n" NOR, me);
                else
                if (di >= 30)
                        message_combatd(HIR "$N" HIR "Ĭ���������ͼ���" +
                                        weapon->name() + HIR "����͸��һ�ɹ�â����˸������\n" NOR, me);
        }

        addn_temp("apply/attack", skill / 3, me);
        addn_temp("apply/dodge", skill / 3, me);
        addn_temp("apply/damage", di, me);
        addn_temp("apply/unarmed_damage", di, me);
        set_temp("powerup", 1, me);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3, di :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int di)
{
        if (query_temp("powerup", me))
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                addn_temp("apply/damage", -di, me);
                addn_temp("apply/unarmed_damage", -di, me);
                delete_temp("powerup", me);
                tell_object(me, "����ټ�ׯ������ϣ��������ջص��\n");
        }
}
