// This program is a part of NITAN MudLIB
// fenglei.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        string msg, msg1;
        int i, count;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("���������񽣡�ֻ����ս���жԶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);
        if( !weapon || query("skill_type", weapon) != "sword"
        ||  me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("�����ʹ���ڽ�ʱ����ʹ�����������񽣡���\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("�����Ӣ�񽣲�����죬����ʹ�á��������񽣡���\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 60)
                return notify_fail("��ı̲�����Ϊ����������ʹ�á��������񽣡���\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("�����̫�ͣ�����ʹ�á��������񽣡���\n");

        if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("��ʹ�õ��ڹ����ԣ�����ʹ�á��������񽣡���\n");

        if( query("neili", me)<400 )
                return notify_fail("����������̫��������ʹ�á��������񽣡���\n");

        i = (me->query_skill("luoying-shenjian", 1) / 4);

        msg = HIG "$N�������������һ�Ӱ����񽣡���������װ�ķ�������! \n" NOR;

        count = attack_power(me, "sword")/10;
        addn_temp("apply/damage", count, me);
        addn_temp("apply/str", count/10, me);
        addn_temp("apply/attack", count, me);
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(WHT"                                                                           ���־�\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIC"                                                                           ���־�\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(MAG"                                                                           ���־�\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIR"                                                                           ���־�\n"NOR,me);
        addn("neili", -200, me);

        me->start_busy(2);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/str", -count/10, me);
        addn_temp("apply/attack", -count, me);

        return 1;
}
