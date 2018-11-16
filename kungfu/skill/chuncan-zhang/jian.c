#include <ansi.h>

#define JIAN "��" HIW "�����Ը�" NOR "��"

inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if( userp(me) && !query("can_perform/chuncan-zhang/jian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( query_temp("ccz_jian", me) )
                return notify_fail("���Ѿ�����" JIAN "�ˡ�\n");

        if ((int)me->query_skill("chuncan-zhang", 1) < 80)
                return notify_fail("��Ĵ����Ʒ�������죬����ʩչ" JIAN "��\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("����ڹ���򲻹�������ʩչ" JIAN "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ����������ʩչ" JIAN "��\n");

        if (me->query_skill_mapped("strike") != "chuncan-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ" JIAN "��\n");

        if (me->query_skill_prepared("strike") != "chuncan-zhang")
                return notify_fail("��û��׼�������Ʒ�������ʩչ" JIAN "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" JIAN "��\n");

        msg = HIW "$N" HIW "�����������ƾ����£���ʱ˫������һ����������ס��������\n\n" NOR;
        message_combatd(msg, me);

        skill = me->query_skill("chuncan-zhang", 1);

        addn_temp("apply/attack", -skill/4, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("ccz_jian", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 4, skill / 3 :), skill / 2);

        addn("neili", -150, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        if( query_temp("ccz_jian", me) )
        {
                addn_temp("apply/attack", a_amount, me);
                addn_temp("apply/dodge", -d_amount, me);
                delete_temp("ccz_jian", me);
                tell_object(me, "���" JIAN "������ϣ��������ջص��\n");
        }
}