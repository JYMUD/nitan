#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        string fam;
        fam=query("family/family_name", me);

        // Ҫ��ֻ�кȹ������̻�ƻ�����������Ҳ���ʩչ
        if (userp(me)
           && fam != "������"
            && !query("skybook/item/xuanbingjiu", me) )
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if (target != me)
                return notify_fail("��ֻ�����޺���ħ���������Լ���ս������\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        if( query("skybook/item/xuanbingjiu", me )
           && fam == "������")
                message_combatd(HIY "$N" HIY "�ߺ�һ����ţ������޺���ħ��"
                                "����ȫ��Ƥ��һ�����" NOR + HIB "����" HIY
                                "ɫ����һ��ȴΪ" HIR "Ѫ��" HIY "ɫ��\n"
                                NOR, me);
        else

        if (fam == "������")
                message_combatd(HIY "$N" HIY "�ߺ�һ����ţ������޺���ħ��"
                                "����ȫ���������ȣ�������֮���͡�\n"
                                NOR, me);

        else
                message_combatd(HIY "$N" HIY "΢һ���������޺���ħ�񹦣�"
                                "ȫ������������ֳ�" NOR + HIB "����" HIY
                                "��" HIR "Ѫ��" HIY "��ɫ��\n" NOR, me);

 
        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("powerup", 1, me);
       

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill);

        if (me->is_fighting())
                me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "����޺���ħ��������ϣ��������ջص��\n");
        }
}