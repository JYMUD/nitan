// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ�ú�ħ������\n");

        if( target != me )
                return notify_fail("��ֻ���ñ��Ϻ�����������ħ������\n");

        if( (skill = me->query_skill("freezing-force", 1)) < 1500 )
                return notify_fail("��ı��Ϻ�����Ϊ�������޷�ʹ�ú�ħ������\n");

        if( me->query_skill("huagong-dafa", 1) < 1500 )
                return notify_fail("��Ļ�������Ϊ�������޷�ʹ�ú�ħ������\n");

        if( me->query_skill("poison", 1) < 1500 )
                return notify_fail("��Ի��������Ĳ��򻹲������޷�ʹ�ú�ħ������\n");

        if( me->query_skill("force", 1) < 1500 )
                return notify_fail("��Ի����ڹ�����Ϊ���������޷�ʹ�ú�ħ������\n");

        if( query_temp("freezing", me) )
                return notify_fail("���Ѿ�������ħ�����ˡ�\n");

        if( query("jingli", me)<2000 )
                return notify_fail("�������������\n");

        if( query("neili", me)<5000 )
                return notify_fail("�������������\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIB "$N" HIB "��ɫ���أ�����һ���������˲���Ϊ����ɫ��$N" HIB "��֮�ڳ��������ص������趯�š�\n"
                       "������Щ��������ˣ���ɫ���������ڿ��о����������������ϳ棬��$N�������в�ֹ��\n"
                       "�����¶��轵��ֻɲ�Ǽ书�򣬿����ƺ��������ˡ���˲�䣬$N" HIB "��ͬ�����壬ʹ�����������\n" NOR, me);

        addn_temp("apply/unarmed_damage", 9000, me);
        addn_temp("apply/avoid_freeze", 90, me);
        addn_temp("apply/add_freeze", 90, me);
        addn_temp("apply/add_poison", 90, me);
        set_temp("freezing", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("freezing", me)){
                addn_temp("apply/add_freeze", -90, me);
                addn_temp("apply/add_poison", -90, me);
                addn_temp("apply/unarmed_damage", -9000, me);
                addn_temp("apply/avoid_freeze", -90, me);
                delete_temp("freezing", me);
                tell_object(me, HIB "$N" HIB "����һ�ͣ��������ǣ������Ϻ�ħ�����ջص��"
                                "�����������ɵĲϳ��������ڣ�\n$N" HIB"����ɫ�ָ���������Χ�ĺ���Ҳ����ɢ���ˡ�\n" NOR);
        }
}
