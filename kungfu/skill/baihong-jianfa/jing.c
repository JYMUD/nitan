// This program is a part of NITAN MudLIB
// jingtian.c  �׺羪�� 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;

        if (! me->is_fighting())
                return notify_fail("���׺羪�졹ֻ����ս����ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                        return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("shenghuo-xuanming", 1) < 100)
                return notify_fail("���ʥ����ڤ����򻹲�����, ����ʹ����һ���� !\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򻹲�����, ����ʹ����һ���� !\n");

        if ((int)me->query_skill("baihong-jianfa", 1) < 100)
                return notify_fail("�����ң������򻹲�����, ����ʹ����һ���� !\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ������\n");

        msg = HIC "\n$N��Хһ�����ֵ�����������Ʈ��������ʹ�����ǰ׺羪�����ľ������׺羪�졹��\n" NOR;
        message_combatd(msg, me);

        me->clean_up_enemy();
        ob = me->select_opponent();
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);

        addn("neili", -random(150)-50, me);
        me->start_busy(1 + random(4));      
        return 1;
}