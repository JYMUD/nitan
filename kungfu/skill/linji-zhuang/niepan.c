// Written by Lonely@nitan.org
// ������� ת������

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        /*
        if( userp(me) && !query("can_exert/linji-zhuang/niepan", me) ) 
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչ������͡�\n");  

        if( query("family/family_name", me) != "������" )
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ�÷�����͡�\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�÷�����ͣ�\n");

        skill = me->query_skill("linji-zhuang", 1);
        if( skill < 1000 )
                return notify_fail("����ټ�ʮ��ׯ��Ϊ���������޷�ʹ�÷�����ͣ�\n");

        if( query("jingli", me)<1000 )
                return notify_fail("�������������\n");

        if( query("neili", me)<2000 )
                return notify_fail("�������������\n");

        if( objectp(target) && target != me ) {
                if( !target->query_weak() )
                        return notify_fail(target->name() + "��û�д�������״̬��\n");

                addn("neili", -1000, me);
                me->receive_damage("qi", 0);
                target->clear_weak();
                message_combatd(HIY "ֻ��$N" HIY "��Ϣ������˫������"+target->name()+"���󣬽������д�С��ׯ��ֻ��"+target->name()+"ȫ����â���֡�\n" NOR, me);
                tell_object(target, HIG"\n��о�����״̬�����ĸ�ԭ�ˡ�����\n\n" NOR);
                tell_object(me, HIG"\n����"+target->name()+"����������״̬������\n\n" NOR);
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        if( query_temp("niepan", me) )
                return notify_fail("���Ѿ��������������ˡ�\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "��ɫ������̾���������ġ�ת˲���ֻ�����ϲ����֮״��\n����$N" HIY "�ſ�����һ�ž���է�ּ��ţ�$N"HIY"����ϰȴ��ȫȻ��ͬ��\n" NOR, me);

        addn_temp("apply/avoid_busy", 100, me);
        addn_temp("apply/avoid_weak", 100, me);
        addn_temp("apply/reduce_damage", 70, me);
        set_temp("niepan", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/2);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("niepan", me)){
                addn_temp("apply/avoid_busy", -100, me);
                addn_temp("apply/avoid_weak", -100, me);
                addn_temp("apply/reduce_damage", -70, me);
                delete_temp("niepan", me);
                tell_object(me, "����ټ�ׯ������ϣ��������ջص��\n");
        }
}
