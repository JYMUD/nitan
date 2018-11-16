// This program is a part of NITAN MudLIB
// suo.c ������

#include <ansi.h>

inherit F_SSERVER;
int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("id", weapon) != "jinshejian" )
                return notify_fail("��û�ý��߽�������ʹ�þ��У�\n");

        if( query("dex", me)<20 || query("str", me)<20 )
                return notify_fail("�����������������, ����ʹ�á�����������\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("jinshe-jian", 1);

        if( !(me->is_fighting() ))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("�Է�û��ʹ�ñ��������ò��ˡ�����������\n");

        if( skill < 150)
                return notify_fail("��Ľ��߽����ȼ�����, ����ʹ�á�����������\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������޷����á�����������\n");

        msg = HIC "$N����"YEL"���߽�"HIC"����һ����⣬б��һ����������������\n"
              YEL "���߽�"HIC"���⵹�����ù���$n��"+weapon2->name()+"�ϡ�\n";
              
        message_combatd(msg, me, target);

        damage = damage_power(me, "sword");
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg = "$n��ʱ������ǰ���һ��������һ������";
                msg += weapon2->name();
                msg += "���ַɳ���\n" NOR;
                me->start_busy(random(2));
                target->receive_damage("qi", damage);
                target->start_busy(2);
                weapon2->move(environment(me));
        }
        else
        {
                addn("neili", -30, me);
                msg = "$n����������������" + weapon2->name()+ "бб˳��һ��һ����˻�����\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}