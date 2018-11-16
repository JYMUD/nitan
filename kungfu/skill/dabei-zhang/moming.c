// This program is a part of NITAN MudLIB
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);      

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ʹĪ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "�Ѿ����ܶ��ˣ�\n");
                
        if( (int)me->query_skill("dabei-zhang", 1) < 100 )
                return notify_fail("��Ĵ��Ʋ�����죬����ʹ�á���ʹĪ������\n");

        msg = HIB "$N����¶��һ˿��ʹ�����飬��������һ�������ӷ�,\n"NOR;
        msg += HIB "˫�ֻ������Ƴ�������ƽ����һ�У����ǿ�����һ˿\n"NOR;
        msg += HIW "�������������Ǵ�������������ʹĪ������\n"NOR;
        
        ap = attack_power(me, "strike");

        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$p��ͼͻ��$N�Ĺ�����Χ�����Ǳ�$N���Ʒ�ܵĺ�����·��\n" NOR;
                target->start_busy(3 +random(4));
                addn("neili", -500, me);
        } else 
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIC "$pһ�ۿ�����$N�����������˹�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

