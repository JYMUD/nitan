// jiang.c �����콵

#include <ansi.h>

inherit F_SSERVER;
string name() { return "�����콵"; }

int perform(object me, object target)
{
        object weapon;
        string msg,force;
        int damage,sk1,sk2,exp1,exp2,skill,dp,ap;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�������콵��ֻ����ս����ʹ�á�\n");


        skill = (int)me->query_skill("shenlong-jian",1);

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( skill < 300 )
                return notify_fail("�����������������죬����ʹ�á������콵����\n");

        if( (int)me->query_skill("busi-shenlong", 1) <100
                 && (int)me->query_skill("shenlong-xinfa", 1)<100)
                return notify_fail("����ڹ���򲻹����޷����ӽ���������\n");

        if( query("neili", me)<600 )
                return notify_fail("����������̫��������ʹ�þ��С�\n");

        if ( me->query_skill_mapped("force") != "busi-shenlong"
                 && me->query_skill_mapped("force") != "shenlong-xinfa")
                 return notify_fail("��û������������ϵ���ڹ���\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        msg = CYN "$N��Ծһ�������󽣾������������дʣ�ͻȻ���һ���������콵������\n"NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if( !target->is_busy() )
                {
                        if(skill<350)
                                target->start_busy(1 + random(2));
                        else
                                target->start_busy(1 + random(3));
                }
                damage = damage_power(me, "sword");

                target->receive_damage("qi", damage/2,me);
                target->receive_damage("jing", damage/3,me);
                target->receive_wound("jing", damage,me);
                addn("neili", -damage, me);
                msg += HIY"$N�Ľ�����ʱ��ù���ʮ�֣��ó���佣������������������Ѹ����$n��ȥ��\n"
                       "$n��ͼ�ܿ����У���ȫ��Ӳ���ܶ������ɻ����Ѿ������������������ӻ��������\n"NOR;
                me->start_busy(3);
        }
        else
        {
                msg += CYN"$n�ٸ����屻�ƣ���֪�������������Ԫ������ͻ�ƶԷ����ơ�\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}

