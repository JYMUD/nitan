// tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra;
        object weapon;
        extra = me->query_skill("tianzhu-juedao",1);

        if ( extra < 150) return notify_fail("������þ������������죡\n");

        if( !target ) target = offensive_target(me);
        if( !target ||        !me->is_fighting(target) )
                return notify_fail("�����þ�ɱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("blade") != "tianzhu-juedao")
                return notify_fail("�㻹û��׼�����þ�����\n");

        if( query("max_neili", me)<1600 )
                return notify_fail("��������Ϊ���㣡\n");
        if( query("neili", me)<600 )
                return notify_fail("������������\n");

        weapon=query_temp("weapon", me);
        addn("neili", -400, me);
        addn("jingli", -100, me);
        msg = HIY  "$Nʹ�����þ����еģ����þ�ɱ�ݣ�һ��������ʽ�����е�"+ 
                  weapon->name()+ HIY"�������$n������\n"
                  "��һ����" NOR;
        message_vision(msg,me,target);
        addn_temp("apply/damage", 200, me);
        addn_temp("apply/attack", 400, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        msg = HIY  "�ڶ�����" NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        msg = HIY  "��������" NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        me->start_busy(3);
        addn_temp("apply/damage", -200, me);
        addn_temp("apply/attack", -400, me);
        return 1;
}