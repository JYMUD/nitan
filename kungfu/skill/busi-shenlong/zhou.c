//zhou.c

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease,dodge_decrease;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("busi-shenlong",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("���䷨��ֻ����ս����ʹ�á�\n");
        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");
        if( (int)me->query_skill("busi-shenlong", 1) < 200)
                return notify_fail(HIM "��Ĳ��������ķ���Ϊ���㣬���޷��������������! \n" NOR);
        if( query("neili", me)<1000 || query("max_neili", me)<2000 )
                return notify_fail("��������������޷�������ԡ�\n");

        message_vision(HIR "\n$NͻȻ���һԾ��˫��������չ���������д�......\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n\n" NOR, me);

        ap=query("combat_exp", me)/1000+skill*5;
        if(living(target))
                dp=query("combat_exp", target)/4000;
        else    dp = 0;

        if( random(ap) > dp * 2 )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIM "$n����$N���е����ͻ���񾭴��ң�ȫ��ʧȥ֪��һ�㣡\n"NOR;
                attack_decrease=query("apply/attack", target)/6;
                dodge_decrease=query("apply/defense", target)/6;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                        target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIR "$n����$N���е����ͻ�о����㱣��ֽŶ�ʱ����ʹ����\n"NOR;
                attack_decrease=query("apply/attack", target)/9;
                dodge_decrease=query("apply/defense", target)/9;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg = CYN "$n�۹۱ǣ��ǹ��ģ���Ԫ��һ������������а����ƣ�\n"NOR;
                if(userp(me))
                        addn("neili", -400, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}