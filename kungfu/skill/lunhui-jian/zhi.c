#include <ansi.h> 

#define CHAN "��" HIR "��ָѨ" NOR "��" 

inherit F_SSERVER; 

int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 

        if( userp(me) && !query("can_perform/lunhui-jian/zhi", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) 
        { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(CHAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" CHAN "��\n"); 

        if (target->is_busy()) 
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n"); 

        if ((int)me->query_skill("force") < 180) 
                return notify_fail("����ڹ���򲻹�������ʩչ" CHAN "��\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 120) 
                return notify_fail("��������ֻؽ��������ң�����ʩչ" CHAN "��\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian") 
                return notify_fail("��û�м��������ֻؽ�������ʩչ" CHAN "��\n"); 

        if( query("neili", me)<100 )
                return notify_fail("�����������������ʩչ" CHAN "��\n"); 

        if (! living(target)) 
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        msg = HIY "$N" HIY "��Ϣ���ȣ�����" + weapon->name() + HIY "ңңָ��$n��" 
              "һ�ɾ�����"+ weapon->name() + HIY "�ϼ��������ֱָ��$n�������Ѩ��\n" NOR; 
        
        if (random(me->query_skill("sword")) > target->query_skill("parry") / 2) 
        {
                msg += HIR "$n" HIR "�Բ��������ϼ���ҪѨ�ѱ�����͸��"
                       "��һʱ���޷�������\n" NOR; 
                target->start_busy((int)me->query_skill("lunhui-jian") / 20 + 1); 
                addn("neili", -60, me);
                me->start_busy(1); 
        } else 
        {
                msg += CYN "����$n" CYN "С��Ӧ�ԣ�˿�����ң�����" 
                       "Ծ����$N" CYN "�ݺὣ���İ�Χ��\n" NOR; 
                addn("neili", -30, me);
                me->start_busy(2); 
        }
        message_combatd(msg, me, target); 

        return 1; 
}
