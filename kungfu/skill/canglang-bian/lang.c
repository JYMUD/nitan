// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;
string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target
        ||      ! target->is_character()
        ||      ! me->is_fighting(target))
                return notify_fail("���������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
        ||      query("skill_type", weapon) != "whip" )
                return notify_fail("��û�б����֣�ʩ�������������졹��\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if (me->query_skill("canglang-bian", 1) < 200)
                return notify_fail("��ġ����˱޷� ��δ�����磬�޷�ʩ�����������졹��\n");

        if (me->query_skill("bibo-shengong", 1) < 200)
                return notify_fail("��ı���������Ϊ�������޷�ʩ�������˱޷�����\n");

        if (me->query_skill_mapped("whip") != "canglang-bian")
                return notify_fail("�����õĲ��ǡ����˱޷� ����ʩչ�������������졹��\n");

        message_combatd(
                HIR"$N��Ȼ��"+(query("name", query_temp("weapon", me)))+
                HIR"ƵƵ˦����"+(query("name", query_temp("weapon", me)))+
                HIR "������ž����֮�������ŵ�$n�ķ����ҡ�\n" NOR, me, target);
        message_combatd(
                HIB "$N��������ǧ������ͷȴ����ָ��$n������ҪѨ��������������������޾���"
                "��$nֻ���м�֮��ȴ�޻���֮����\n" NOR, me, target);

        set_temp("julang", 1, me);

        skill =  ( me->query_skill("canglang-bian") + me->query_skill("dodge") ) / 2;

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -200, me);
        me->start_busy(random(2));

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill/3);

        return 1;
}

private int remove_effect(object me, int amount)
{
        if( query_temp("julang", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("julang", me);
                message_combatd(YEL "\n$N���������ڹ���������ѹ�£�\n\n" NOR, me);
        }

        return 0;
}