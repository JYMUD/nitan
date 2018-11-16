#include <ansi.h>

inherit F_CLEAN_UP;

#define FIREICE "��" HIW "��" HIR "��" HIW "������" NOR "��"

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        string fam;
        fam=query("family/family_name", me);

        if( userp(me) && !query("skybook/item/xuanbingjiu", me) )
                 return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if (target != me)
                return notify_fail("��ֻ����" FIREICE "�������Լ���ս������\n");

        if( query_temp("fireice", me) )
                return notify_fail("����������ʩչ" FIREICE "��\n");

        if ((int)me->query_skill("luohan-fumogong", 1) < 180)
                return notify_fail("���޺���ħ������㣬����ʩչ" FIREICE "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" FIREICE "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" FIREICE "��\n");

        skill = me->query_skill("luohan-fumogong", 1);
        addn("neili", -300, me);
        me->receive_damage("qi", 0);

        message_combatd(HIC "$N" HIC "������Х����ת��" HIW "��"
                        HIR "��" HIW "������" HIC "������������"
                        "���Ƽ䣬�⻪������ɷΪ׳�ۡ�\n" NOR, me);

        addn_temp("apply/unarmed_damage", skill*4, me);
        addn_temp("apply/damage", skill*4, me);
        addn_temp("apply/armor", skill*4, me);
        set_temp("fireice", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill * 4 :), skill);

        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("fireice", me) )
        {
                addn_temp("apply/unarmed_damage", -amount, me);
                addn_temp("apply/damage", -amount, me);
                addn_temp("apply/armor", -amount, me);
                delete_temp("fireice", me);
                tell_object(me, "���" FIREICE "������ϣ��������ջص��\n");
        }
}