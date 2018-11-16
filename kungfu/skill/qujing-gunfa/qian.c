#include <ansi.h>
#include <combat.h>

#define TUN "��" HIR "Ǭ���޼�" NOR "��"

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail(TUN "������ù���ʩչ��\n");

        if( query_temp("qujing_qian", me) )
                return notify_fail(TUN "�޷�����ʩչ��\n");

        if ((int)me->query_skill("qujing-gunfa", 1) < 180)
                return notify_fail("���Ǭ���޼���Ϊ����������ʩչ" TUN "��\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" TUN "��\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")

                return notify_fail("��û�м���ȡ������Ϊ����������ʩչ" TUN "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" TUN "��\n");


        msg = HIY "$N" HIY "˫�ֳֵ���������������ʩ����Ǭ���޼���ѧ��"
              HIR "Ǭ���޼�" HIY "����\n��ʱ��Х������������һ�������ޱȵ��"
              "��$N" HIY "����ӿ�����ƹ���$N" HIY "��ȥ��\n" NOR;
        message_sort(msg, me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("qujing-gunfa",1);
        set_temp("qujing_qian", 1, me);
        addn_temp("apply/attack", skill*3/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/weapon_damage", skill/3, me);
        addn("neili", -600, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("qujing_qian", me) )
        {
                addn_temp("apply/attack", -(skill*3/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/weapon_damage", -(skill/3), me);
                delete_temp("qujing_qian", me);
                tell_object(me, "�㾭��������Ϣ���ֿ��Լ���ʩչ��" HIR "Ǭ���޼�" NOR "���ˡ�\n");
        }
}

