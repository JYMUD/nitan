// dan.c ������˫

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("��������˫��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("���á�������˫�����б����н���\n");

        if ((int)me->query_skill("snowstar-sword", 1) < 200)
                return notify_fail("���ѩӰ���ǽ���������죬����ʹ�á�������˫����\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á�������˫����\n");
                        
        msg = HIW "\n$N" HIW "��̨�������������ߣ�������磬����" + weapon->name() + HIW "����һ����ƥ����Ľ��⣬���޻��ڵĴ���$n" HIW "��\n\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                if (weapon2)
                {
                        msg += HIR "\n$n" HIR "��$N" HIR "�������ͣ���æ�ֵ��£�����" + weapon2->name() + HIR "����ɼ��أ����ѵ�����\n" NOR;
                        damage -= damage/3;
                        weapon2->set_name("���ѵ�"+query("name", weapon2));
                        weapon2->move(environment(target));
                        set("value", 0, weapon2);
                        set("weapon_prop", 0, weapon2);
                        target->reset_action();
                }
                msg += HIR "$n" HIR "����������׾��һ������ʱ��������������������" + weapon->name() + HIR "���Լ����ؿڴ�����Ŀ����͸��һ�ֲ���˼�����ɫ��\n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$n" HIR "��æ������Ծ�������ѳ��˽���İ�Χ��\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}