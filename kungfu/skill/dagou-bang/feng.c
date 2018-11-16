// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���־�" NOR; }

int perform(object me, object target)
{
        object weapon;
        string wp;
        int skill;

        if (! target) target = offensive_target(me);

        if( query_temp("feng_zijue", me) )
                return notify_fail("����������ʩչ" + name() + "��\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        skill = me->query_skill("dagou-bang", 1);

        if (skill < 120)
                return notify_fail("��򹷰���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        wp = weapon->name();

        message_combatd(HIG "$N" HIG "ʹ���򹷰�����" HIY "��"
                        HIG "���־�������" + wp + HIG "������"
                        "�����ó������Ӱ��ס����\n" NOR, me);

        addn("neili", -150, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("feng_zijue", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill / 2);

        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("feng_zijue", me) )
        {
                addn_temp("apply/defense", -amount, me);
                delete_temp("feng_zijue", me);
                tell_object(me, "���" + name() + "ʩչ��ϣ��������ջص��\n");
        }
}
