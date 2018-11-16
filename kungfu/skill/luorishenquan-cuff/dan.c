// dan.c ����

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
                return notify_fail("�����ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if(me->query_skill_mapped("cuff") != "luorishenquan-cuff") 
                return notify_fail("��û����������ȭ���޷�ʹ�á����ա����У�\n");

        if (me->query_skill_prepared("cuff") != "luorishenquan-cuff")
                return notify_fail("��û��׼��ʹ��������ȭ���޷�ʩչ�����ա����С�\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("��������˫�ֲ���ʹ��ȭ�����С�\n");

        if ((int)me->query_skill("luorishenquan-cuff", 1) < 200)
                return notify_fail("���������ȭ������죬����ʹ�á����ա���\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á����ա���\n");
                        
        msg = HIY "\n$N" HIY "���췢��һ����Ц��ʹ��������ȭ�ľ��У����գݣ�\n"
              "���Ʋ����ޱȵ�Ϧ������ʱ�������Ϊ֮��ɫ��\n" NOR;

        ap = me->query_skill("cuff") + me->query_skill("force");
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

                msg += HIR "\nֻ����ž��һ�����죬$N" HIR "��˫ȭ�Ѿ�������$n" HIR "��\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                msg += HIY "$n" HIY "����һ�����ܿ���$N" HIY "����һ�С�\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}