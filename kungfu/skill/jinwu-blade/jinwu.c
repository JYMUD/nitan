
// jinwu.c ���ڶ��

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR"���ڶ��"NOR; } 

int perform(object me,object target)
{
        string msg;
        object weapon;
        int ap, dp, qi_wound;
        int temp;
        string skill, fskill,bskill;

        if( !objectp(target) ) {target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||       
                !me->is_fighting(target) ||
                !living(target) )
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = query_temp("weapon",me)) ||
                query("skill_type", weapon) != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        
        skill  = "jingwu-blade";    
        fskill = "bingxue-xinfa";
        bskill = "blade";

        if( (int)me->query_skill(skill, 1) < 200 )
                return notify_fail("���"+to_chinese(skill)+"�ȼ�����, ����ʹ��"+name()+"��\n");
                
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("���"+to_chinese(fskill)+"�ȼ�����, ����ʹ��"+name()+"��\n");

        if( me->query("max_neili") < 1000 )
                return notify_fail("���������Ϊ�������޷����á�"+HIR"���ڶ��"NOR+"����\n");

        if( me->query("neili") < 400 )
                return notify_fail("��������������޷����á�"+HIR"���ڶ��"NOR+"����\n");

        msg = HIY"$N����Ծ��,ʹ��"+HIR"�����ڶ�ء�"HIY"������"NOR+weapon->name()+HIY"�Ӱ���лӵ�ֱ��������\n"
              "��������������ߣ��������ǳ�ɳ����ܲ���Ҷ�����缤�����Ŷ��裬\n��$n�Ӷ��˱ܵĿ�϶�������ʵʵ��\n"NOR;
        message_combatd(msg, me, target);
        msg = "";

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");
        if (target->query_skill_mapped("parry") == "xueshan-sword")
        {
                msg += HIR "$n" HIR "��æ��æ��"HIW"ѩɽ����"HIR"�����ֵ�����֪$N"
                       HIR "��������ѩɽ�������ǰ㣬\n" + weapon->name() +
                       HIR "��â��ʱ�ֱ�����������ȫ����$n" HIR "����"
                       "�н��У�\n" NOR;
                ap = ap * 2;
                temp = 1;
        }       

        if( random(ap) + ap / 2 > dp )
        {
                if(userp(me)) me->add("neili",-250);
                msg += HIC"$n���޿ɱܣ�ֻ��һ�ɸ���֮���ľ������������ʹ��ֱ����Ϣ��\n"
                        "$n�������˸�����ȴֻ��"NOR""+weapon->name()+""HIC"����һ��������ͣϢ��һ���������š�\n"NOR;
                qi_wound = damage_power(me, "blade")+me->query_str()*10;
                qi_wound *= 2;
                if (temp != 1) //�Ը���ѩɽ����
                {
                        qi_wound = random(qi_wound);
                        if(qi_wound > query("qi", target)) qi_wound = 100;
                }
                target->receive_damage("qi", qi_wound);
                target->receive_wound("qi", query("max_qi", target)/3);
                target->start_busy(2+random(1));
                me->start_busy(1+random(1)); 
        }
        else
        {
                if(userp(me)) me->add("neili",-100);
                msg += HIW"����$n�������Ա�һ�����ܹ���$N���ɱ��һ����\n"NOR;
                me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);
        return 1;
}

