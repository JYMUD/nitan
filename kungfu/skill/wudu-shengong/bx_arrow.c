// bx_arrow.c ��Ѫ��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int success, ap, dp;


/*
  if ( userp(me) && !wizardp(me) && 
  !query("perform/bx_arrow", me) && 
  !query("can_perform/wudu-shengong/bx_arrow", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�");
*/

        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
            !living(target) || query_temp("noliving", target) )
                return notify_fail("��Ѫ��ֻ����ս����ʹ�á�\n");
        if( !userp(me))
                return notify_fail("ֻ����Ҳ���������\n");

        if( query("max_neili", me)<400 )
                return notify_fail("�������������������Чʩչ��Ѫ����\n");

        if((int)me->query_skill("force",1) < 50 ||
                (int)me->query_skill("wudu-shengong",1) < 50 )
                return notify_fail("����ڹ���Ϊ������������Чʩչ��Ѫ����\n");

        if( query("combat_exp", me)<query("combat_exp", target)/10 )
                return notify_fail("�Է��书ǿ��ʮ�����������õģ����ǿ��ܰɣ�\n");

        message_combatd( HIC
 "$N˫ĿѪ�죬��ͷɢ�������췢��һ����Х��\n\n$N����һ�ᣬ���Լ�������һҧ����������������һ���涾Ѫ����$n���˹�ȥ��\n" NOR,me,target);

        success = 1;
        ap = me->query_skill("force",1)+me->query_skill("wudu-shengong",1);
        ap = ap /2 ;
        ap = ap * ap * ap/10;
        ap=ap+query("combat_exp", me);
//        ap = ap * ap;
        dp=query("combat_exp", target);
//        dp = dp * dp;
        if( random(ap+dp) < random(dp) ) success = 0;

        ap=query("max_neili", me);
        dp=query("max_neili", target);
        if( ap < random(dp) ) success = 0;

        if(success == 1 )
        {
                message_combatd(HIR"���$n�ٲ�������Ѫ��������ţ���ʱ����һ���ҽУ�$N��״������Цһ������ǰһ�ڵ��ڵ��ϡ�\n" NOR,me,target);

                target->kill_ob(me);
                me->kill_ob(target);
                addn("max_neili", -50, me);
                me->save();

                target->receive_wound("qi",query("max_qi", target)+1,me);
                target->receive_wound("jing",query("max_jing", target)+1,me);
                COMBAT_D->report_status(target);

                me->receive_wound("qi",query("max_qi", me)+1,target);
                me->receive_wound("jing",query("max_jing", me)+1,target);
                COMBAT_D->report_status(me);
        }
        else {
                message_combatd(HIR"����Ѫ����$n�������𣬻���һ��Ѫ����ɢƮȥ��\n$Nһ����Ц����̾һ������ǰһ�ڵ��ڵ��ϡ�\n" NOR,me,target);
                target->kill_ob(me);
                me->kill_ob(target);

                addn("max_neili", -30, me);
                me->save();

                me->receive_wound("qi",query("max_qi", me)+1,target);
                me->receive_wound("jing",query("max_jing", me)+1,target);
                COMBAT_D->report_status(me);
        }

        return 1;
}

int help(object me)
{
        write(WHT"\n�嶾��֮��Ѫ��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �����Լ�һ�������ͶԷ�ƴ��

        ����Ҫ��
                �嶾��50��
                �����ڹ�50��
                ����400
                �Է����鲻�������ʮ��
HELP
        );
        return 1;
}
