#include <combat.h>
#include  <ansi.h>

#define HUI "��" WHT "����" HIW "��Ӱ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{

        int ap, dp;
        object env;

        if( userp(me) && !query("can_perform/kuihua-mogong/fenshen", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 460)
                return notify_fail("�����ħ����Ϊ����������ʩչ" HUI "��\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("��������Ϊ����������ʩչ" HUI "��\n");

          if( query("jingli", me)<1000 )
                return notify_fail("�㾫�����㣬����ʩչ" HUI "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("���������㣬����ʩչ" HUI "��\n");
        
        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if( query_temp("hiding_kuihua", me) )
                return notify_fail("�������˹��У�\n");

        ap=me->query_skill("dodge")+query("dex", me);
        dp=target->query_skill("dodge")+query("dex", target);

        env = environment(me);
        
         me->start_busy(1);
         addn("neili", -800, me);
         addn("jingli", -400, me);

        message_sort(HIY "\n$N��Цһ����ʩչ�����������䡷����֮��ѧ" + HUI + HIY + 
                     "��ɲ�Ǽ䣬" + env->short() + HIY + "�û�������$N����Ӱ��\n" NOR, me);
        
        if (target->query_skill("count") > 100 && random(2))
        {
                message_sort(HIC "\n$Nʩչ���������Եľ�ѧ����$n��" + HUI + HIC "���⡣\n" NOR, target, me);
                return 1;
        }

        if (ap / 2 + random(ap) > dp)
        {
                message_sort(HIG "\n$N�پ��ۻ����ң�ʧȥ�˷���\n" NOR, target);
                target->remove_enemy(me);
                set_temp("hiding_kuihua", 1, me);
                addn("jingli", -200, me);
                target->start_busy(4 + random(4));
                call_out("del_hiding", 20 + random(me->query_skill("kuihua-mogong", 1) / 30), me);
        }
        else
        {
                message_sort(HIM "\n$N�Ͻ�����ס����С�ĵ��ƶ��ŽŲ�����$n���л��⡣\n" NOR, target, me);
        }
                
        return 1;
}

void del_hiding(object me)
{

        if (! objectp(me))return;

        delete_temp("hiding_kuihua", me);

        tell_object(me, HIG "�����Ӱ��ʩչ��ϣ��������ջص��\n");

        return;
}