
/*
��־ƽ��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����еġ������������С���־���������ţ�
�ӽ���������־ƽ�������֣������Է���ȥ���������١���һ����˫�������

������⼸��������ã��ѷǼ�֮��֪������������ȫ���亹���ۼ���־�����ڰ�գ�һ�����飬һ
����ʵ������������Ҫ��������۹Ƕϡ���֪��־������������Σ���쳣֮�ʺ�Ȼ���з�������Ѱ
�ɣ��������ɵ�����������
*/


#include <ansi.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        int skill;
        string weapon;
        int damage;
        string *limb, type, result, str;
        int ap, dp, pp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if( objectp(query_temp("weapon", me)) )
                return notify_fail("������������ֲ���ʩչ��\n");

        if( me->query_skill_mapped("strike") != "chongyang-shenzhang" )
                return notify_fail("�����õĲ����������ƣ�����ʩչ�������У�\n");

        if( me->query_skill_prepared("strike") != "chongyang-shenzhang" )
                return notify_fail("�������Ĳ����������ƣ�����ʩչ�������У�\n");

        //if( me->query_skill_mapped("force") != "xiantian-gong" )
        //        return notify_fail("�����õĲ����������칦��ʩչ�����������У�\n");

        if( me->query_skill("force") < 120 )
                return notify_fail("����ڹ����δ�����޷�ʩչ�������У�\n");

        if( me->query_skill("strike") < 120 )
                return notify_fail("����������Ҫ��տ���������Ʒ�����Чʩչ��\n");

        if( query("neili", me) <= 200 )
                return notify_fail("�����������ʹ���������У�\n");

        message_combatd(HIY "$Nŭ��һ�����վ�ȫ����ͻȻ����㹥��ָ���ơ����������У�\n\n" NOR, me, target);

        skill = me->query_skill("strike")/2 + me->query_skill("strike") / 8;

        addn_temp("apply/attack", skill, me);

        if( me->query_skill_prepared("strike") == "chongyang-shenzhang" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("strike");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        if( query_temp("restore", me))me->prepare_skill("strike","chongyang-shenzhang");

        if( me->query_skill_prepared("finger") == "zhongnan-zhi" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("finger");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        if( query_temp("restore", me))me->prepare_skill("finger","zhongnan-zhi");
        addn_temp("apply/attack", -skill, me);

        message_combatd( HIY "\n������$NͻȻ�ڿշ���ʹ��һ��ԧ�������ȣ����ȷ�۵糸��������$n\n" NOR,me,target);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        pp = defense_power(target, "parry");
        if( ap / 2 + random(ap) > dp )
        {
                if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
                {
                        message_combatd(HIR"ֻ��$Nһ���ҽУ����������������Ŀڡ�����$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
                        damage=query("eff_qi", target);
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage=query("qi", target);
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
                        addn("neili", -query("jiali", me), me);
                }
                else
                {
                        damage=damage_power(me, "strike");
                        addn("neili", -query("jiali", me), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", damage/2, me);

                        limb=query("limbs", target);
                        type = "����";
                        message_combatd("ֻ��$Nһ���ҽУ���������������$P"+limb[random(sizeof(limb))]+"�������$P��ˤ�˸���ͷ��\n",target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                }
                me->start_busy(1+random(2));
        }
        else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
        //else if( ap / 2 + random(ap) < pp )
        {
                message_combatd(HIR"$N�;��þ�����������֪�����æ���������$n���˸��գ��װ��Լ����ص���һ�ӡ�\n\n"NOR, target,me );
                me->start_busy(2+random(2));
        }
        else
        {
                message_combatd( "$N�ۼ���һ���������ͣ�����˫��һ�㣬Ծ���ĳߣ��㿪��$n��һ�У�����Ҳ����һ���亹��\n\n" NOR,  target,me);
                me->start_busy(2);
        }

        addn("neili", -random(me->query_skill("strike")/4)-100, me);

        return 1;
}
