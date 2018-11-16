// Written by Lonely@nitan.org
// �������� ת������
// wuzhi.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;

        /*
        if( query("family/family_name", me) != "��Ĺ��" )
                return notify_fail("�㲻�ǹ�Ĺ���ӣ��޷�ʹ���������͡�\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ���������ͣ�\n");

        if( (skill = me->query_skill("yunv-xinfa", 1)) < 1000 )
                return notify_fail("�����Ů�ķ����������죬�޷�ʹ���������ͣ�\n");

        if( query_temp("wuzhi", me) )
                return notify_fail("���Ѿ����������������ˡ�\n");

        if( query("jingli", me)<2000 )
                return notify_fail("�������������\n");

        if( query("neili", me)<5000 )
                return notify_fail("�������������\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        skill += me->query_skill("martial-cognize", 1);
        skill /= 100;

        message_combatd(HIY "ֻ��$N" HIY "�ľ���ˮ����Ϣ����ͣ�ͣ�������ѧ����ˮ�����������\n" NOR, me);

        addn_temp("apply/ap_power", skill, me);
        addn_temp("apply/add_weak", skill, me);
        addn_temp("apply/add_busy", skill/6, me);
        addn_temp("apply/double_damage", skill, me);
        set_temp("wuzhi", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill*50);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("wuzhi", me)){
                addn_temp("apply/ap_power", -skill, me);
                addn_temp("apply/add_weak", -skill, me);
                addn_temp("apply/add_busy", -skill/6, me);
                addn_temp("apply/double_damage", -skill, me);
                delete_temp("wuzhi", me);
                tell_object(me, "�����Ů�ķ�������ϣ��������ջص��\n");
        }
}
