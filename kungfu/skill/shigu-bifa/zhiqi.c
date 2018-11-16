// poqizhen.c ������
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("shigu-bifa",1);

        if( !(me->is_fighting() ))
                return notify_fail("��������ֻ����ս�������ڶ������ϡ�\n");
 
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "dagger" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( skill < 80)
                return notify_fail("�����ĸ�뷨��������, ����ʹ�á�����\n");

        if( query("neili", me)<150 )
                return notify_fail("��������������޷����á���������\n");
 
        msg = HIR "$N���һ����$n�����������㣬�����ǡ��ᡱ�ֵ��������ʣ����϶��µĻ���������\n";
        message_vision(msg, me, target);
 
        ap = me->query_skill("dagger") + skill;
        dp = target->query_skill("force") / 3;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -100, me);
                msg = HIR"$N�ʼ�˿������ĵ��жԷ�Ҫ��, $n��ʱ���õ�����һ���ʹ��\n";
                msg += HIR"ȫ��������й������\n" NOR;

                neili_wound = 1000 + random(skill);
                if( neili_wound>query("neili", target) )
                        neili_wound=query("neili", target);

                qi_wound = neili_wound / 5;
                if( qi_wound>query("qi", target) )
                        qi_wound=query("qi", target);
                if(qi_wound < 0) qi_wound = 0;

                addn("neili", -neili_wound, target);
                addn("qi", -qi_wound, target);
                addn("eff_qi", -qi_wound, target);
                target->start_busy(3);me->start_perform( 4+random(3), "��������");
}
        else
        {
                if(userp(me))
                        addn("neili", -80, me);
                msg = HIW"����$n˲�䷴Ӧ��������Ų��Ծ�����������ش���\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}