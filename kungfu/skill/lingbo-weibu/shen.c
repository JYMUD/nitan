// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "������" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʩչ" + name() + "��\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("����貨΢������������������ʩչ" + name() + "��\n" NOR);

        if( query("jingli", me)<2000 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n" NOR);

        if( query("neili", me)<5000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n" NOR);

        if( query_temp("immortal", me) )
                return notify_fail("���Ѿ�����" + name() + "��\n" NOR);

        if( time() - query_temp("last_immortal", me) < 20 )
                return notify_fail("���޷����������Ƶ�ʹ��" + name() + "��\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("immortal", 1, me);

        msg = MAG "\n$N" MAG "����������ʩչ" + name() + "��������Σ���⽻������ѷ֣��������Կ������ڡ�\n" NOR;

        message_combatd(msg, me);
        set_temp("last_immortal", time(), me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if( query_temp("immortal", me) )
        {
                delete_temp("immortal", me);
                tell_object(me, "��ġ������ϡ��˹���ϣ��������ջص��\n");
        }
}
