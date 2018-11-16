// zhua.c ������ץ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHUA "��" HIR "������צ" NOR "��"

int perform(object me, object target)
{
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUA "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail(ZHUA "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 280)
                return notify_fail("��ľ����񹦻�������죬����ʹ��" ZHUA "��\n");
                                
        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ��" ZHUA "��\n");

//        if (me->query_skill_prepared("claw") != "jiuyin-shengong")
        if (me->query_skill_mapped("claw") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" ZHUA "��\n");
       
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "΢΢һЦ�����ֳ�צ������ץ��$n"
              HIY "��ҪѨ��\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        me->want_kill(target);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$N" HIR "��һצ���ƺÿ죬��ץ��$n"
                               HIR "��̴�д�Ѩ��$n" HIR
                               "һ���ҽУ��������̱����ȥ��\n" NOR;
                        damage = -1;
                } else
                {
                        if (! target->is_busy())
                        target->start_busy(1 + random(3));
        
                        damage = damage_power(me, "claw");
                        
                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "Ҫ��";
                        pmsg = HIR "$n��æ��Ų������Ȼ�������ꡱһ����$N"
                               HIR "��ָ������$n" HIR "��" + limb + "��$n"
                               HIR "һ���ҽУ�Ѫ���岽��\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "������$P"
                       CYN "�����ƣ���Ӧ�÷����ܿ�����һץ��\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
