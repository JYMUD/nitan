// This program is a part of NT MudLIB
// ������� ת������
// buddha.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( userp(me) && !query("can_exert/yijinjing/buddha", me) ) 
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչ������ա�\n");  
        /*
        if( query("family/family_name", me) != "������" )
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ�÷�����ա�\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�÷�����գ�\n");

        if( target != me )
                return notify_fail("��ֻ�����׽������������ա�\n");

        if( (skill = me->query_skill("yijinjing", 1)) < 1000 )
                return notify_fail("����׽��û��ѧ�ɣ��޷�ʹ�÷�����գ�\n");

        if( me->query_skill("jingang-buhuaiti", 1) < 1000 )
                return notify_fail("��Ľ�ղ���������Ϊ�������޷�ʹ�÷�����գ�\n");

        if( me->query_skill("buddhism", 1) < 1000 )
                return notify_fail("��������ķ��Ĳ��򻹲������޷�ʹ�÷�����գ�\n");

        if( me->query_skill_mapped("parry") != "jingang-buhuaiti" )
                return notify_fail("����뼤����ղ����壬����ʹ�÷�����գ�\n");

        if( query_temp("buddha", me) )
                return notify_fail("���Ѿ��������������ˡ�\n");

        if( query("jingli", me)<2000 )
                return notify_fail("�������������\n");

        if( query("neili", me)<5000 )
                return notify_fail("�������������\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "ֻ��$N" HIY "�ߺ���ţ����������գ����Ǽ�ȫ������ƽ�һ�㣬�����Ӳӽ�⡣\n" NOR, me);

        addn_temp("apply/avoid_busy", 90, me);
        addn_temp("apply/avoid_weak", 90, me);
        addn_temp("apply/reduce_damage", 90, me);
        set_temp("buddha", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("buddha", me)){
                addn_temp("apply/avoid_busy", -90, me);
                addn_temp("apply/avoid_weak", -90, me);
                addn_temp("apply/reduce_damage", -90, me);
                delete_temp("buddha", me);
                tell_object(me, "��������ϣ��������ջص�������ʧ��\n");
        }
}
