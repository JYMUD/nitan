// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���䰵��"; }

void remove_shoot(object);

int perform(object me, object target)
{
        int t=query_temp("baituo/shoot", me);
        string type, *limbs, str, dodge_skill, limb, result;
        object weapon;
        int poi_amount, level, exp1, exp2;

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ�ܷ��䰵����\n");

        if( !target && me->is_fighting()) target = offensive_target(me);

        if (!target || !target->is_character())
                return notify_fail("��Ҫ��˭���䰵����\n");

        if( target == me )
                return notify_fail("���Լ����䰵����\n");

        if( t && (time()-t) < 10 )
                return notify_fail("��ողŷ����˰�������ʱ���ڲ��˹ʼ���ʩ��\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("������ֳ��ܷ��䰵�������ȡ�\n");

        type=query("snake_type", weapon);

        if( !type && query("id", weapon) != "shezhang" )
                return notify_fail("���"+weapon->name()+"�ϲ�û�а������ء�\n");

        level = (int)me->query_skill("lingshe-zhangfa", 1);
        if (level < 40 )
                return notify_fail("��������ȷ�������죬�޷����ݷ��䰵���Ļ��ء�\n");

        if ((int)me->query_skill("poison", 1) < 40 )
                return notify_fail("��Ļ�����������̫ǳ���޷����ݷ��䰵���Ļ��ء�\n");

        if(( me->query_skill_mapped("force") != "hama-gong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("�����õ��ڹ��롸�����ȷ�����·��㣣�\n");

        limbs=query("limbs", target);
        //level = level/2;
        poi_amount = level + me->query_skill("poison", 1);

        if( query("neili", me)<poi_amount )
                return notify_fail("�������������\n");
        if( query("jingli", me)<50 )
                return notify_fail("��ľ���������\n");

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);

        if(exp1*3<exp2 && exp2> 1000000)
                return notify_fail("����֪"+target->name()+"������֣���ͷ����Ҳ�κ������ã����粻�������ǳ�Ц��\n");

        message_combatd(HIB"$N��"+weapon->name()+HIB"�ڵ���һ�٣��ص�һ�����죬��ͷ�зɳ�һ�����ΰ�������ֱ��$n��ȥ��\n"NOR, me, target);

        addn("neili", -poi_amount/2, me);
        addn("jingli", -50, me);

        if( query("neili", me)>random(query("neili", target)) && (exp1/100)>random(exp2/100)){

                message_combatd(HIR"�ǰ���ȥ�úÿ죬����$nһ���Һ�����δ���尵����·���ѱ�����"+(arrayp(limbs)?limbs[random(sizeof(limbs))]:"����")+"��\n"NOR, me, target);

                if( type == "����" || type == "����" )
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                else
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                set("poisoner", me, target);
                target->receive_wound("qi", random(level) + level/2 , me);
                target->start_busy(random(2));
                result=COMBAT_D->eff_status_msg(query("qi", target)*100/query("max_qi", target));
                message_combatd("( $N"+result+" )\n", target);

        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                str = SKILL_D(dodge_skill)->query_dodge_msg(limb);
                message_vision(str, me, target);
        }

        target->kill_ob(me);
        set_temp("baituo/shoot", time(), me);
        call_out("remove_shoot", 5, me);
        me->start_busy(random(2));

        return 1;
}

void remove_shoot(object me)
{
        if( !me || !query_temp("baituo/shoot", me))return ;

        delete_temp("baituo/shoot", me);
        tell_object(me, "���������İ���׼�����ˡ�\n");
}
