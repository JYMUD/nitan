// pozhang.c ������ʽ��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, wound;

        if( query("family/master_id", me) != "fengqingyang" )
           return notify_fail("�㲻�Ƿ�����ĵ��ӣ�����ʹ�þ��У�\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lonely-sword",1);

        if( !(me->is_fighting() ))
            return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if( objectp(weapon2=query_temp("weapon", target)) )
            return notify_fail("�Է������������������ò��ˡ�����ʽ����\n");

        if( skill < 70)
            return notify_fail("��Ķ��¾Ž��ȼ�����, ����ʹ�á�����ʽ����\n");

        if( query("neili", me)<50 )
            return notify_fail("��������������޷����á�����ʽ����\n");

        msg = HIC "$Nʹ�����¾Ž�֮������ʽ��, �������ڽ��⣬��ͼ����ʹ��.\n";
        message_combatd(msg, me, target);

        ap=query("combat_exp", me)+skill*1000;
        dp=query("combat_exp", target)/4;
        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -50, me);
            msg = "$N��������ʽ��, $n��ʱ������ǰһ��������һ������������һ
�ؽ���ð�˳�����\n"NOR;

//            wound = 60 + random(skill);
            wound = (int)me->query_skill("sword",1)/2 + skill;
            wound = wound/2 + random(wound);
// modify by Java
            if( wound>query("qi", target) )
                wound=query("qi", target);
            me->start_busy(random(2));
//            target->addn("qi", -wound);
//            target->addn("eff_qi", -wound);
            target->receive_damage("qi", wound);
            target->receive_wound("qi", wound/2);
// modify by Java
            target->start_busy(2);
        }
        else
        {
            if(userp(me))
                addn("neili", -100, me);
            msg = "����$n������$N����ͼ��ȫ�����أ�������ס��$N�Ĺ��ơ�\n"NOR;
            me->start_busy(random(3));
        }
        message_combatd(msg, me, target);
        return 1;
}
int help(object me)
{
        write(WHT"\n���¾Ž�֮����ʽ��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �ƽ���ֲ����ĵ���֮���������˵���Ѫ

        ����Ҫ��
                ��Ϊ������մ�����
                ���¾Ž�50��
                ����50
HELP
        );
        return 1;
}
