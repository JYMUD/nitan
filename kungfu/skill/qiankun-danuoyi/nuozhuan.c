// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "ŲתǬ��" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʩչ" + name() + "��\n" NOR);

        if( (level = me->query_skill("qiankun-danuoyi", 1)) < 1000 )
                return notify_fail("���Ǭ����Ų�ƻ���������������ʩչ" + name() + "��\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n" NOR);

        if (query_temp("nuozhuan", me))
                return notify_fail("���Ѿ�����" + name() + "��\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("nuozhuan", 1, me);
        msg = MAG "\n$N" MAG "����������Ĭ��" + name() + "�ķ�������ж�����еķ����Ѵ﷢����Ȼ֮����\n" NOR;

        message_combatd(msg, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/60);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)query_temp("nuozhuan", me))
        {
                delete_temp("nuozhuan", me);
                tell_object(me, "��ġ�ŲתǬ�����˹���ϣ��������ջص��\n");
        }
}
