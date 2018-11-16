#include <ansi.h>

#define HUA "��" MAG "����ͨ��" NOR "��"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int skill;

        if( !query("scborn/ok", me) )
                return notify_fail("����ʹ�õ��⹦��û��������ܡ�\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian")
                return notify_fail("�㻹û�м������¾Ž���\n");
                
        if( !query("can_learn/dugu-jiujian/nothing", me) )
                return notify_fail("�㻹û�н������о��磬��̸����ͨ����\n");
                
        if ((int)me->query_skill("dugu-jiujian", 1) < 1000)
                return notify_fail("��Ķ��¾Ž��ȼ�����������ʩչ" HUA "��\n");
                                        
        if( query_temp("dugu_sword", me) )
                return notify_fail("���Ѿ�����" HUA "�ˡ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("����ʹ�õ��������ԣ�\n");
                
        if( query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�\n");
                
        if( query("neili", me)<250 )
                return notify_fail("���ʱ���������㣬����ʩչ" HUA "��\n");

        msg = MAG "$N" MAG "����������������б����������������ң�����ͨ�����磡\n\n" NOR;

        message_combatd(msg, me, target);

        if (me->is_fighting())
                me->start_busy(1);

        skill = me->query_skill("dugu-jiujian", 1);

        addn_temp("apply/damage", skill*2, me);
        set_temp("dugu_sword", 1, me);

        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, skill * 2 :), 180);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("dugu_sword", me) )
        {
                addn_temp("apply/damage", -1*amount, me);
                delete_temp("dugu_sword", me);
                tell_object(me, "���" HUA "������ϣ��������ջص��\n");
        }
}