// xiangmo.c �޺���ħ����ʮ���޺���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        
        if (! target) target = offensive_target(me);
    if( userp(me) && !query("can_perform/luohan-gun/xiangmo", me) )
                return notify_fail("��ʹ�õ��⹦��û��������ܣ�\n");
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("���޺���ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("luohan-gun", 1) < 100) 
        return notify_fail("����޺�����������죬���ڻ��޷�ʹ�á��޺���ħ����\n");
                                
        if( query("neili", me)<150 )
        return notify_fail("�����������������޷����á��޺���ħ����\n");
                
        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�˵�һ����һ��ƽƽ��$n"
              HIY "ɨ������ʽ��Ȼ�򵥣�����ȴҲ���������ء�\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = 100 + ap / 5 + random(ap / 5);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "ֻ��$n" HIR "һ���м�ʧ�󣬵�ʱ"
                                           "��������˸����ţ��ƺ�һ��������һ����\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "����$p" CYN "����һ�񣬼�ס��$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}