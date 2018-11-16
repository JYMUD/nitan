#include <ansi.h>
#include <combat.h>

string name() { return HIR "תǬ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 220)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 200)
                return notify_fail("�������������Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��ȫ��������һָ��ָ�����ն�ʮ���޷�λ�ƹ��������"
              "���һ�����" HIR "תǬ��" HIC "��������\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("qimen-wuxing", 1);
        dp = defense_power(target, "dodge") + target->query_skill("qimen-wuxing", 1);
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "���Ǽ�$n" HIR "ֻ����âһ����$N" HIR "ʳָ"
                               "������$p" HIR "ӡ�ð�ߣ�ָ����ʱ���Զ��롣\n"
                               HIW "���������ۡ���һ�������Ͼ�Ȼ���������Խ���"
                               "\n" NOR "( $n" RED "���˹��أ��Ѿ�������в���"
                               "����ʱ�����ܶ�����" NOR ")\n";
                        message_combatd(msg, me, target); 
                        damage = -1;
                } else
                if (query_temp("thd/tz", me) && random(3) != 1) 
                {
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        msg += HIY "\n�ۿ���$n" HIY "�ѱ�����ҪѨ" 
                               ",$Nǿ��һ����������˫��������һ����ָ��\n"  
                               "��ʱ��$n�Ƶ����޿��ˣ�\n\n" NOR; 
                        
                        for (int i = 0; i < (int)random(9); i++) 
                        {
                                if (! me->is_fighting(target))  
                                        break;  
                                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100, 
                                        HIR "���Ǽ�$n" HIR "ֻ����âһ����$N" 
                                        HIR "ʳָ������$p" HIR "���ð�ߣ�ָ��"  
                                        "��ʱ������롣\n���������͡���һ����"  
                                        "���Ͼ�Ȼ����������Ѫ��\n" NOR); 
                        }
                        message_combatd(msg, me, target); 
                        addn("neili", -300, me);
                        me->start_busy(1 + random(3)); 
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        damage+= fmsk;
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 175 + fmsk / 10, 
                                                   HIR "���Ǽ�$n" HIR "ֻ����âһ����$N"
                                                   HIR "ʳָ������$p" HIR "���ð�ߣ�ָ��"
                                                   "��ʱ������롣\n���������͡���һ����"
                                                   "���Ͼ�Ȼ����������Ѫ��\n" NOR);
                        message_combatd(msg, me, target); 
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -300, me);
                msg += CYN "$p" CYN "��$P" CYN "��ʽ���أ����д�"
                       "�⣬��ʱ���Ծ���ɣ�����������\n" NOR;
                message_combatd(msg, me, target); 
        }

        if (damage < 0)
        {
                target->receive_damage("qi", 100, me);
                target->die(me);
        }

        return 1;
}
