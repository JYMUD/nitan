// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "Բ����" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me)
{
        object weapon;
        string wp;
        int skill;

        if( query_temp("yuan_man", me) )
                return notify_fail("����������ʩչ" + name() + "��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("��û�м��������ַ�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("riyue-lun", 1) < 120)
                return notify_fail("��������ַ�����㣬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        wp = weapon->name();

        message_combatd(HIY "$N" HIY "����������ʩ�������ַ���" HIW "Բ����"
                        HIY "��������" + wp + HIY "��ת��ɣ�Ѹ�ٻ�ס����Ҫ"
                        "����\n" NOR, me);

        skill = me->query_skill("riyue-lun", 1);

        addn("neili", -200, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("yuan_man", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill / 2);

        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("yuan_man", me) )
        {
                addn_temp("apply/defense", -amount, me);
                delete_temp("yuan_man", me);
                tell_object(me, "���" + name() + "������ϣ��������ջص��\n");
        }
}

