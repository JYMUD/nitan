
//�ٲ����У���־ƽ��ƽ�̣�����������ͬʱ���Ⱥ�ɨ������
//����ȫ�����еġ������������С�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "������"; }

int perform(object me, object target)
{
        int addon, ap, dp, damage, count, limit, limit2;
        string str;
        object weapon, weapon1;

        weapon=query_temp("weapon", me);
        weapon1=query_temp("secondary_weapon", me);

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("�������޽������ʹ��ȫ�潣����������������\n");

        if(!target ) target = offensive_target(me);

        if(!target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("sword",1)<150)
                return notify_fail("��Ļ�������������ʵ��\n");

        if (me->query_skill("quanzhen-jian",1)<180)
                return notify_fail("���ȫ�潣����Ϊ������\n");

        if( me->query_skill_mapped("sword") != "quanzhen-jian" )
                return notify_fail("�����õĲ���ȫ�潣����\n");

        if( query("neili", me) <= 350 )
                return notify_fail("�����������ʹ�á�����������\n");

        if( query("jingli", me) <= 250 )
                return notify_fail("��ľ�������ʹ�á�����������\n");

        if( me->query_skill_mapped("strike") != "haotian-zhang" &&
            me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("�����õĲ���ȫ����Ʒ�������ʩչ������������\n");

         if( me->query_skill_prepared("strike") != "haotian-zhang" &&
             me->query_skill_prepared("strike") != "chongyang-shenzhang")
                return notify_fail("�������Ĳ���ȫ����Ʒ�������ʩչ������������\n");

        addn_temp("quanzhen/lh_count", 1, me);

        if( query_temp("quanzhen/lh_count", me)>30 )
                set_temp("quanzhen/lh_count", 1, me);

        addn("neili", -350, me);
        addn("jingli", -250, me);
        me->start_busy(3);

        count=query_temp("quanzhen/lh_count", me);
        limit=180;
        if (count<=10) tell_object(me, HIG"\n\n�㾫���ӣ��������棬���и���������\n\n"NOR);
        if (count>10 && count<=20) {
                tell_object(me, HIG"\n\n�㷴��ʹ�á����������������Ѿ�û����ǰ����������Ȼ���ͱ��ˡ�\n\n"NOR);
                limit=120;
        }
        if (count>20) {
                tell_object(me, HIG"\n\n��ʹ��̫��Ρ�����������������ɢ�������Ѿ�ʧȥ��ԭ�е�������\n\n"NOR);
                limit=60;
        }

        addon = me->query_skill("sword")/4;
        if (addon > limit) addon = limit;

        addn_temp("apply/attack", addon, me);
        addn_temp("apply/damage", addon/2, me);

        message_vision(HIR"������У�$N��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����еġ������������С�\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, weapon, 1);

        weapon->unequip();
        if (objectp(weapon1))     weapon1->unequip();

        COMBAT_D->do_attack(me, target, 0, 1);

        weapon->wield();
        if (objectp(weapon1))     weapon1->wield();

        ap=query("combat_exp")/1000+me->query_skill("sword", me)+me->query_skill("unarmed",1);
        dp=query("combat_exp")/1000+target->query_skill("parry", target);

        if(me->query_skill("unarmed",1)>50) message_vision(HIY,me,target);
        message_vision("\n$N��һ�䣬৵�һ�ȣ�������$n��ɨ������ֻ���õ��ϳ������\n"NOR,me,target);

        if(random(ap)>dp/2 || !living(target))
        {
                damage=me->query_skill("quanzhen-jian",1)*(random(6)+3);

                message_vision(HIR"\nֻ��$n�����������Ѿ���$Nһ��ɨ�У��ҽ����У�����������\n"NOR, me, target);

                if (damage<500) damage=500;

                if (limit==100) damage=200;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);

                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                message_vision("($N"+str+")\n", target);

                target->start_busy(3);
        } else {
                message_vision(HIY"\n$n�������������ͣ����һԾ�����ɵض��˿�ȥ��\n"NOR,me,target);
                if(limit==100)
                {
                        message_vision(HIR"\n$N�������ͣ����Ʋ�ס������Ӵ��һ����ˤ��һ����\n"NOR,me,target);
                        addn("eff_qi", -random(400), me);
                        str=COMBAT_D->status_msg(query("qi", me)*100/query("max_qi", me));
                        message_vision("($N"+str+")\n", me);
                }
                me->start_busy(2);
        }

        addn_temp("apply/attack", -addon, me);
        addn_temp("apply/damage", -addon/2, me);
        return 1;
}
