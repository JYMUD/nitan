// zhen.c ̫��ȭ�����־�

#include <ansi.h>
#include <combat.h>

string name() { return "���־�"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        string force;

        if(! target) target = offensive_target(me);

        if(! target || ! target->is_character() || ! me->is_fighting())
                return notify_fail("��" + name() + "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á�" + name() + "����\n");

        if((int)me->query_skill("taiji-quan", 1) < 180)
                return notify_fail("���̫��ȭ������죬����ʹ�á�" + name() + "����\n");

        if((int)me->query_skill("force", 1) < 200)
                return notify_fail("����ڹ������ߣ��������������˵С�\n");

        if( query("neili", me)<1000 )
                return notify_fail("����������̫������Ҳ���˵��ˡ�\n");

        msg = HIY "$N" HIY "Ĭ���񹦣�������ת��˫������������һ��ԲȦ�ѽ�$n"
              HIY "��ס��\n̫��ȭ�еġ�" HIW + name() + HIY "������ʹ����һ��"
              HIY "����������$n" HIY "��ȥ��\n" NOR;

        ap = attack_power(me, "cuff") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                if( query("neili", me)<query("neili", target) )
                {
                        damage = damage_power(me, "cuff");
                        damage+= query("jiali", me);

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                                   HIC "\n�ۼ�$P" HIC "��Ҫ��$p�𵹣�ͻȻ��$n"
                                                   HIC "����ȫ��������ǿ����ʹӲ����$Pһ�С�\n" NOR);
                        if (! target->is_busy())
                                target->start_busy(3);
                        me->start_busy(3);
                        addn("neili", -(query("neili", target)/2), target);
                        addn("neili", -(query("neili", me)/(2+random(2))), me);
                }
                else
                {
                        damage = damage_power(me, "cuff");
                        damage+= query("jiali", me);

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300,
                                                   HIC "\n�ۼ�$n" HIC "��$P������ѹ��͸����������ֻ����$N"
                                                   HIC "���顱��һ������$n" HIC "��$pȫ���������ɢ��"
                                                   HIC "��һ�㵹����ȥ��\n" NOR);
                        me->start_busy(2);
                        if( !target->is_busy() )
                                target->start_busy(3);
                        addn("neili", -(query("neili", me)/(2+random(3))), me);
                }
        }
        else
        {
                msg += HIG "\n��$p�����ֱ��$P���ȫ�����������ܿ����ŵ�$P�����޴룡\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target, 0, 1);
        return 1;
}
