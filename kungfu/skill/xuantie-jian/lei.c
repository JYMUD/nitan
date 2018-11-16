// This program is a part of NITAN MudLIB
// lei.c Ѹ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "Ѹ��"; }

int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;

        j = me->query_skill("xuantie-jian", 1);
        z = me->query_skill("surge-force", 1);

        weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��Ѹ�ס�ֻ����ս���жԶ���ʹ�á�\n");

       if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("�������ʹ�ý�ʱ����ʹ����Ѹ�ס���\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian")
                return notify_fail("��Ļ����мܱ�������������ʱ����ʹ����Ѹ�ס���\n");

        if(me->query_skill("xuantie-jian", 1) < 160 )
                return notify_fail("�������������������죬ʹ������Ѹ�ס���\n");

        if(me->query_skill("surge-force", 1) < 160 )
                return notify_fail("���ŭ��������Ϊ������ʹ������Ѹ�ס���\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("����ڹ��ȼ�������ʹ������Ѹ�ס���\n");

        if( (int)me->query_str() < 32)
                return notify_fail("���������������ʹ������Ѹ�ס���\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("�������������ʹ������Ѹ�ס���\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("����������̫����ʹ������Ѹ�ס���\n");

        if( query("neili", me)<900 )
                return notify_fail("����������̫����ʹ������Ѹ�ס���\n");

        addn_temp("apply/str", z/6, me);
        addn_temp("apply/attack", j/6, me);
        addn_temp("apply/damage", z/2, me);

        msg = BLU "\n$N�����е�"+weapon->name()+"������$nһѹ����Ȼ����һ���� һ����Ϊ�Ľ������籼�׳��繥��$n��\n\n"NOR;
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -500, me);

        addn_temp("apply/str", -z/6, me);
        addn_temp("apply/attack", -j/6, me);
        addn_temp("apply/damage", -z/2, me);

        me->start_busy(2);
        if( !target->is_busy() )
                target->start_busy(1);
        return 1;
}
