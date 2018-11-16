// This program is a part of NITAN MudLIB
// leidong.c �׶�����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�׶�����"; }

int perform(object me, object target)
{
        string msg;
        int improve;
        object weapon=query("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�׶�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ���׶����죡\n");

        if ((int)me->query_skill("poyu-quan", 1) < 80)
                return notify_fail("�������ȭ������죬����ʹ���׶����죡\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 80)
                return notify_fail("�����ϼ�񹦲����ߣ������ó��׶������˵С�\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan"
                || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("�������޷�ʹ�á��׶����졹���й�����\n");

        if( query("neili", me)<200 )
                return notify_fail("����������̫�����޷�ʹ���׶����졣\n");

        if( query_temp("leidong", me) )
                return notify_fail("������ʹ���׶����죡\n");

        msg = MAG "$N" MAG "ʹ����ʯ����ȭ�ľ�ѧ�׶����죬��ʱ��յ���������\n" NOR;
        message_combatd(msg, me, target);

        improve=query("dex", me);
        improve+=query("str", me);
        addn_temp("apply/dex", improve, me);
        addn_temp("apply/str", improve, me);
        set_temp("leidong", 1, me);

        addn("neili", -150, me);
        if (! target->is_busy())
        target->start_busy(random((int)me->query_skill("poyu-quan", 1) / 100 + 2));
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, improve :),
                            me->query_skill("poyu-quan", 1) / 5);
        return 1;
}

void remove_effect(object me, int improve)
{
        if( query_temp("leidong", me) )
        {
                addn_temp("apply/dex", -improve, me);
                addn_temp("apply/str", -improve, me);
                delete_temp("leidong", me);
        }
}

