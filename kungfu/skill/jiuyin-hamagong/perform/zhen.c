#include <ansi.h>
#include <combat.h>

#define ZHEN "��" WHT "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/jiuyin-hamagong/zhen", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHEN "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("jiuyin-hamagong", 1) < 250)
                return notify_fail("�������󡹦��򲻹�������ʩչ" ZHEN "��\n");
                
        if ((int)me->query_skill("unarmed", 1) < 250)
                return notify_fail("������Ʒ�û���ã�����ʩչ" ZHEN "��\n");        

        if (me->query_skill_mapped("unarmed") != "jiuyin-hamagong")
                return notify_fail("��û�м���������󡹦������ʩչ" ZHEN "��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return notify_fail("��û��׼��������󡹦������ʩչ" ZHEN "��\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���Ϊ����������ʩչ" ZHEN "��\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("���������Ϊ����������ʩչ" ZHEN "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ��������㣬����ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ͻȻ���ص�˻�����а��������󡹦�ķ�������ð��˿˿���������㣬һ������\n"        
                  "�ɵ���ֱӿ���ϣ�$N�漴��ȻԾ����գ�ʹ���� "HIY "������" HIY "����˫�ƽ�ȫ��������ͣ\n"

                  "������ɲ�Ǽ䣬��ɳ��ʯ���̳�����������������ɽ������ǧ���������$nȫ���ȥ��\n" NOR;  

        ap=me->query_skill("unarmed")+query("str", me)*5;
        dp=target->query_skill("parry")+query("str", target)*5;

        if( query("max_neili", me)>query("max_neili", target)*2 )
        { 
                msg += HIY "$n" HIR "ȫȻ�����赲������$N" 
                       HIY "һȭ���÷������صĵ����ڵ��ϡ�\n" NOR; 
                addn("neili", -50, me);
                me->start_busy(1); 
 
//                message_combatd(msg, me, target); 

   
                target->start_busy(5); 
                set("qi", 1, target);
                set("eff_qi", 1, target);
  
        } else

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "\n$n" HIR "����$N" HIR "��ʹ����˹�����ͬС������ʽ������ʽ"
                       "��ʱ�м�ɢ�ң��������У�ȫ������˺�Ѱ�ʹ�࣬����߷��ݰ㵯����֮Զ!\n" NOR;
                count = ap / 6;
        } else
        {
                msg += HIC "$n" HIC "������з�ͬС�ɣ�����С���æ"
                       "�������������壬����ȫ������ס$N" HIC "��������\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(8) < 3 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -600, me);
        me->start_busy(1 + random(8));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return 1;
}
