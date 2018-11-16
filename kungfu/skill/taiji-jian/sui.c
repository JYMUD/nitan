// This program is a part of NITAN MudLIB
// sui.c ���־�

#include <ansi.h>

string name() { return "���־�"; }

inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��" + name() + "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("�����ý�����ʩչ��" + name() + "����\n");

        if ((int)me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("���̫������������죬����ʹ�á�" + name() + "����\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 80)
                return notify_fail("���̫���񹦻�򲻹�������ʩչ��" + name() + "����\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("�������������\n");

        if( query_temp("tjj_sui", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("taiji-jian");
        msg = HIC "$Nʹ��̫���������桹�־�����Ȧ����С������" + weapon->name() +
              HIC "�ó������⻷��������ס��\n" NOR;
        message_combatd(msg, me, target);

        addn_temp("apply/attack", -skill/6, me);
        addn_temp("apply/defense", skill*6, me);
        set_temp("tjj_sui", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill/6, skill*6 :), skill);

        addn("neili", -query("max_neili", me)/50, me);
        if(me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        addn_temp("apply/attack", a_amount, me);
        addn_temp("apply/defense", -d_amount, me);
        delete_temp("tjj_sui", me);
        tell_object(me, HIG "��ġ�" + name() + "��������ϣ��������ջص��\n" NOR);
}
