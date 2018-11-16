#include <ansi.h>

inherit F_SSERVER;

int second_hit(object me, object target);
int duo(object me, object target);
int duo2(object me, object target);

string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        mapping myfam;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���������ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

         /*
        if( (int)me->query_skill("xiantian-gong",1) < 150 )
                return notify_fail("�����칦��Ϊ���㣡\n");
         */

        if( (int)me->query_skill("taoism",1) < 150 )
                return notify_fail("���ѧ��Ϊ��Ϊ���㣡\n");

        if( me->query_skill("duanyun-bian",1) < 150 )
                return notify_fail("��ġ����Ʊ޷�����Ϊ���㣡\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("��ı޷��Ļ���������ʵ��\n");

        if( me->query_con() < 40 )
                return notify_fail("��ĸ���̫�\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�����������ʹ�á��������ա���\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("�㲢û��װ������Ϊ������\n");

        /*
        if( query("combat_exp", me)/100>query("shen", me) )
                return notify_fail("�����������̫�ͣ��޷���ס���е�а�ʹ������������\n");
        */

        if( query_temp("duanyun", me) )
                return notify_fail("������ʹ�á��������ա����С�\n");

        message_combatd(HIW"\n$N����ƽ�ͣ����������Ʊ޷�ʹ��Բת���⣬����"+(query("name", query_temp("weapon", me)))+HIW"�������ݶ�������������⣬�����Ʋʽ�$n�𽥰�Χ�����С�\n\n"NOR,me,target);

        set_temp("duanyun", 1, me);

        addn("neili", -me->query_skill("whip")/2, me);

        call_out("second_hit", 1, me, target);

        return 1;
}

int second_hit(object me, object target){

        int ap, dp, damage;
        string str;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon",me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N�������ޱޣ��޷������м�����ֻ���˹����С�\n"NOR,me);
                return 1;
        }

        if(me->is_fighting()){

                message_vision(HIY"\n$N�����ĵ���һ����Х���У���$n�͵ط������У�˲ʱ��������ⶸɢ������������\n"NOR, me, target);

                addn("jiali", me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", me->query_skill("whip",1), me);
                addn_temp("apply/damage", me->query_skill("whip",1), me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn("jiali", -me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", -me->query_skill("whip",1), me);
                addn_temp("apply/damage", -me->query_skill("whip",1), me);

                ap=query("combat_exp")/100+me->query_skill("whip", me)+query("neili", me);
                if (living(target))
                      dp=query("combat_exp")/100+target->query_skill("whip", target)+query("neili", target);
                else  dp = 1;
                message_combatd(HIY"\n���й���$N����һ�䣬����"+query("name", query_temp("weapon", me))+HIY"�ڿ��л���һ�����ߣ���$n���䡣\n"NOR,me,target);

                if(random(ap)>dp/2){

                        message_combatd(HIR"\nֻ����$nһ���ҽУ�"+query("name", query_temp("weapon", me))+HIR"�Ѿ�����$n��ͷ����Ѫ����һ�ء�\n\n"NOR,me,target);

                        damage=me->query_skill("duanyun-bian",1)*(random(6)+3);

                        if (damage<500) damage=500;
                                if (damage>2000) damage=2000;

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2,me);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);

                } else if(random(ap)>dp/3 && objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n�������������ͣ�æ��������"+query("name", query_temp("weapon", target))+HIG"�мܡ�\n",me,target);
                        message_combatd(HIW"\n$N����΢��Ѿ���$n���е�"+query("name", query_temp("weapon", target))+HIW"��ס������ͬʱ�����ضᡣ\n"NOR,me,target);

                        me->start_busy(3);
                        target->start_busy(3);

                        call_out("duo", 3, me, target);

                        return 1;

                } else if(random(ap)>dp/3 && !objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n������ת��΢΢һ���Ѿ�������ץס������ͬʱ�����ضᡣ\n"NOR,me,target);

                        me->start_busy(4);
                        target->start_busy(4);

                        call_out("duo2", 3, me, target);

                        return 1;

                } else if(random(ap)>random(dp)) {

                        message_combatd(HIY"\n$n�������������ͣ���֮�����������\n"NOR, me, target);

                        message_combatd(HIG"\n$Nһ�����У�����һת����������һ�У��͵���$n��ȥ��\n"NOR,me,target);

                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                } else
                        message_combatd(HIY "\n$n�������������ͣ�æ���Ծ����\n"NOR,me,target);

                me->start_busy(2+random(2));
        } else
                message_combatd(HIY "\n$N��ս���ѱأ�����������һ�������������ջء�\n"NOR, me);

        delete_temp("duanyun", me);
        return 1;
}

int duo(object me, object target)
{
        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N�������ޱޣ��޷������м�����ֻ���˹����С�\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N�������������͵ؽ�"+query("name", query_temp("weapon", me))+HIG"���һ������$n���е�"+query("name", query_temp("weapon", target))+HIG"�������ֶ����������˵��ϡ�\n"NOR,me,target);

                        message_combatd(HIG"\n$N˳�־���һ�У���$n��ȥ��"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        query_temp("weapon", target)->move(environment(me));

                        target->start_busy(2+random(3));
                } else {

                        message_combatd(HIG"\n$n�������������͵ؽ�"+query_temp("weapon",query("name",  target))+HIG"���һ������$N���е�"+query("name", query_temp("weapon", me))+HIG"�������ֶ����������˵��ϡ�\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\nֻ��$N��$n���������������ض��Լ��ı��У����˵��·��������ĵ���������硣\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\nֻ��$n����һ�Σ��ƺ���Щ֧�ֲ�ס��\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\nֻ��$N����һ�Σ��ƺ���Щ֧�ֲ�ס��\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}

int duo2(object me, object target){

        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N�������ޱޣ��޷������м�����ֻ���˹����С�\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N�������������͵ؽ�"+query("name", query_temp("weapon", me))+HIG"��أ�˳�־���һ�У���$n��ȥ��"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));


                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        target->start_busy(random(3));

                } else {

                        message_combatd(HIG"\n$n�������������͵ؽ�$N���е�"+query("name", query_temp("weapon", me))+HIG"�������ֶ����������˵��ϡ�\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\nֻ��$N��$n���������������ضᣬ���˵��·��������ĵ���������硣\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\nֻ��$n����һ�Σ��ƺ���Щ֧�ֲ�ס��\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\nֻ��$N����һ�Σ��ƺ���Щ֧�ֲ�ס��\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo2", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}
