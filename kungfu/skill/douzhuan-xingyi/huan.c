
// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "���ǻ���" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;

        if( (level = me->query_skill("douzhuan-xingyi", 1)) < 1000 )
                return notify_fail("��Ķ�ת���ƻ���������������ʩչ" + name() + "��\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n" NOR);

        if (query_temp("yixinghuanyue", me))
                return notify_fail("���Ѿ�����" + name() + "��\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("yixinghuanyue", 1, me);
        msg = MAG "\n$N" MAG "����������Ĭ��" + name() + "�ķ��������Ա�֮������֮��ķ����Ѵ﷢����Ȼ֮����\n" NOR;

        message_combatd(msg, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/60);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)query_temp("yixinghuanyue", me))
        {
                delete_temp("yixinghuanyue", me);
                tell_object(me, "���"+name()+"�˹���ϣ��������ջص��\n");
        }
}

